/*
 * implement a container like std::set
 */
#ifndef TICKET_SET_HPP
#define TICKET_SET_HPP

#include <functional>
#include <istream>
#include <ostream>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace tic {
	template<
		class Key,
		class Compare = std::less<Key>
	> class set {
		public:
			typedef Key value_type;

		private:
			struct Node {
				value_type *pvalue;
				int height, size;
				Node *par, *lson, *rson, *prev, *next, *pend;
				int index;
				Node(){}
				Node( value_type * pvalue, int height, int size, Node *par, Node *lson, Node *rson, Node *prev, Node *next, Node *pend )
					:pvalue(pvalue),height(height),size(size),par(par),lson(lson),rson(rson),prev(prev),next(next),pend(pend){}
			};
			Node *pend;
			Compare cmp;

			inline bool equal( const Key &lhs, const Key &rhs ) const {
				return !(cmp(lhs,rhs) || cmp(rhs,lhs));
			}
			inline void update( Node *nd ) {
				nd->height = max( nd->lson->height, nd->rson->height ) + 1;
				nd->size = nd->lson->size + nd->rson->size + 1;
			}
			Node *build( Node **pool, Node *par, int l, int r ) {
				if( l > r ) {
					return pend;
				} else if( l == r ) {
					Node *nd = pool[l];
					nd->par = par;
					nd->lson = nd->rson = nd->pend = pend;
					nd->size = nd->height = 1;
					return nd;
				} else {
					int mid = (l + r) >> 1;
					Node *nd = pool[mid];
					nd->lson = build( pool, nd, l, mid - 1 );
					nd->rson = build( pool, nd, mid + 1, r );
					nd->par = par;
					nd->pend = pend;
					update( nd );
					return nd;
				}
			}
			void clear( Node *nd ) {
				if( nd == pend ) return;
				clear( nd->lson );
				clear( nd->rson );
				delete nd->pvalue;
				delete nd;
			}
			void right_rotate( Node *b ) {
				Node *a = b->par;
				Node *p = a->par;
			
				a->lson = b->rson;
				b->rson->par = a;
				b->rson = a;
				a->par = b;

				b->par = p;
				if( p->lson == a )
					p->lson = b;
				else
					p->rson = b;

				update( a );
				update( b );
				if( p != pend ) update( p );
			}
			void left_rotate( Node *b ) {
				Node *a = b->par;
				Node *p = a->par;

				a->rson = b->lson;
				b->lson->par = a;
				b->lson = a;
				a->par = b;

				b->par = p;
				if( p->lson == a )
					p->lson = b;
				else
					p->rson = b;

				update( a );
				update( b );
				if( p != pend ) update( p );
			}
			void maintain( Node *nd ) {
				Node *b, *c, *top;
				if( nd->lson->height > nd->rson->height + 1 ) {
					if( nd->lson->lson->height > nd->lson->rson->height ) {
						//	LL
						b = nd->lson;
						right_rotate( b );
						top = b;
					} else {
						//	LR
						b = nd->lson;
						c = b->rson;
						left_rotate( c );
						right_rotate( c );
						top = c;
					}
				} else if( nd->rson->height > nd->lson->height + 1 ) {
					if( nd->rson->lson->height > nd->rson->rson->height ) {
						//	RL
						b = nd->rson;
						c = b->lson;
						right_rotate( c );
						left_rotate( c );
						top = c;
					} else {
						//	RR
						b = nd->rson;
						left_rotate( b );
						top = b;
					}
				} else {
					top = nd;
				}
				if( top->par == pend ) return;
				update( top->par );
				maintain( top->par );
			}
			pair<Node*,bool> insert( Node *nd, const value_type & value ) {
				if( equal( *nd->pvalue, value ) ) {
					return pair<Node*,bool>(nd,false);
				} else if( cmp( *nd->pvalue,value) ) {
					if( nd->rson == pend ) {
						Node *next = nd->next;
						Node *nnd = new Node( new value_type(value), 1, 1, nd, pend, pend, nd, next, pend );
						next->prev = nnd;
						nd->next = nnd;
						nd->rson = nnd;
						update( nd );
						maintain( nd );
						return pair<Node*,bool>(nnd,true);
					} else {
						return insert( nd->rson, value );
					}
				} else {
					if( nd->lson == pend ) {
						Node *prev = nd->prev;
						Node *nnd = new Node( new value_type(value), 1, 1, nd, pend, pend, prev, nd, pend );
						nd->prev = nnd;
						prev->next = nnd;
						nd->lson = nnd;
						update( nd );
						maintain( nd );
						return pair<Node*,bool>(nnd,true);
					} else {
						return insert( nd->lson, value );
					}
				}
			}
			Node *find( Node *nd, const Key & key ) const {
				if( nd == pend ) return nd;
				if( equal( *nd->pvalue, key ) ) return nd;
				if( cmp( *nd->pvalue, key ) ) return find( nd->rson, key );
				else return find( nd->lson, key );
			}
			void erase( Node *nd ) {
				if( nd->lson != pend && nd->rson != pend ) {
					Node *next = nd->next;
					if( next == nd->rson ) {
						Node *par = nd->par;
						if( par->lson == nd ) par->lson = next;
						else par->rson = next;
						nd->lson->par = next;
						if( next->rson != pend )
							next->rson->par = nd;
						nd->rson = next->rson;
						next->rson = nd;
						next->lson = nd->lson;
						nd->lson = pend;
						next->par = par;
						nd->par = next;

						nd->prev->next = next;
						next->next->prev = nd;
						nd->next = next->next;
						next->prev = nd->prev;
						nd->prev = next;
						next->next = nd;

						swap( nd->size, next->size );
						swap( nd->height, next->height );

						erase( nd );
					} else {
						Node *ndpar = nd->par;
						Node *nxpar = next->par;
						if( ndpar->lson == nd ) ndpar->lson = next;
						else ndpar->rson = next;
						if( nxpar->lson == next ) nxpar->lson = nd;
						else nxpar->rson = nd;

						nd->prev->next = next;
						next->next->prev = nd;
						nd->next = next->next;
						next->prev = nd->prev;
						nd->prev = next;
						next->next = nd;

						nd->lson->par = next;
						nd->rson->par = next;
						next->rson->par = nd;
						swap( nd->lson, next->lson );
						swap( nd->rson, next->rson );
						swap( nd->par, next->par );
						swap( nd->size, next->size );
						swap( nd->height, next->height );
						erase( nd );
					}
				} else {
					Node *prev = nd->prev, *next = nd->next;
					prev->next = next;
					next->prev = prev;

					if( nd->lson == pend && nd->rson == pend ) {
						Node *par = nd->par;
						if( par->lson == nd ) {
							par->lson = pend;
						} else {
							par->rson = pend;
						}
						if( par != pend ) {
							update( par );
							maintain( par );
						}
						delete nd->pvalue;
						delete nd;
					} else if( nd->rson == pend ) {
						Node *par = nd->par;
						if( par->lson == nd ) {
							par->lson = nd->lson;
						} else {
							par->rson = nd->lson;
						}
						nd->lson->par = par;
						if( par != pend ) {
							update( par );
							maintain(par);
						}
						delete nd->pvalue;
						delete nd;
					} else if( nd->lson == pend ) {
						Node *par = nd->par;
						if( par->lson == nd ) {
							par->lson = nd->rson;
						} else {
							par->rson = nd->rson;
						}
						nd->rson->par = par;
						if( par != pend ) {
							update( par );
							maintain(par);
						}
						delete nd->pvalue;
						delete nd;
					} 
				}
			}

		public:
			class const_iterator;
			class iterator {
			private:
				Node *node;
				Node *get() const {
					return node;
				}

			public:
				friend class set;
				iterator( Node *nd ) {
					node = nd;
				}
				iterator() {
					// TODO
					node = 0;
				}
				iterator(const iterator &other) {
					// TODO
					node = other.node;
				}
				iterator &operator=( const iterator &other ) {
					this->node = other.get();
					return *this;
				}
				/**
				 * return a new iterator which pointer n-next elements
				 *   even if there are not enough elements, just return the answer.
				 * as well as operator-
				 */
				/**
				 * TODO iter++
				 */
				iterator operator++(int) {
					if( node == 0 || node == node->pend ) throw invalid_iterator();
					else { 
						iterator res(*this);
						node = node->next;
						return res;
					}
				}
				/**
				 * TODO ++iter
				 */
				iterator & operator++() {
					if( node == 0 || node == node->pend ) throw invalid_iterator();
					else {
						node = node->next;
						return *this;
					}
				}
				/**
				 * TODO iter--
				 */
				iterator operator--(int) {
					if( node == 0 || node->prev == node->pend ) throw invalid_iterator();
					else {
						iterator res(*this);
						node = node->prev;
						return res;
					}
				}
				/**
				 * TODO --iter
				 */
				iterator & operator--() {
					if( node == 0 || node->prev == node->pend ) 
						throw invalid_iterator();
					else {
						node = node->prev;
						return *this;
					}
				}
				/**
				 * a operator to check whether two iterators are same (pointing to the same memory).
				 */
				value_type & operator*() const {
					if( node == 0 || node == node->pend ) throw invalid_iterator();
					return *node->pvalue;
				}
				bool operator==(const iterator &rhs) const {
					return node == rhs.node;
				}
				bool operator==(const const_iterator &rhs) const {
					return node == rhs.node;
				}
				/**
				 * some other operator for iterator.
				 */
				bool operator!=(const iterator &rhs) const {
					return node != rhs.node;
				}
				bool operator!=(const const_iterator &rhs) const {
					return node != rhs.node;
				}

				/**
				 * for the support of it->first. 
				 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
				 */
				value_type* operator->() const noexcept {
					return node->pvalue;
				}
			};
			class const_iterator {
			// it should has similar member method as iterator.
			//  and it should be able to construct from an iterator.
			private:
				// data members.
				const Node * node;
				const Node * get() const {
					return node;
				}
			public:
				friend class set;
				const_iterator() {
					node = 0;
				}
				const_iterator(const const_iterator &other) {
					node = other.get();
				}
				const_iterator(const iterator &other) {
					node = other.get();
				}
				const_iterator &operator=( const iterator &other ) {
					this->node = other.get();
					return *this;
				}
				const_iterator &operator=( const const_iterator &other ) {
					this->node = other.get();
					return *this;
				}
				// And other methods in iterator.
				// And other methods in iterator.
				// And other methods in iterator.
				/**
				 * return a new iterator which pointer n-next elements
				 *   even if there are not enough elements, just return the answer.
				 * as well as operator-
				 */
				/**
				 * TODO iter++
				 */
				const_iterator operator++(int) {
					if( node == 0 || node == node->pend ) throw invalid_iterator();
					else { 
						const_iterator res(*this);
						node = node->next;
						return res;
					}
				}
				/**
				 * TODO ++iter
				 */
				const_iterator & operator++() {
					if( node == 0 || node == node->pend ) throw invalid_iterator();
					else {
						node = node->next;
						return *this;
					}
				}
				/**
				 * TODO iter--
				 */
				const_iterator operator--(int) {
					if( node == 0 || node->prev == node->pend ) throw invalid_iterator();
					else {
						const_iterator res(*this);
						node = node->prev;
						return res;
					}
				}
				/**
				 * TODO --iter
				 */
				const_iterator & operator--() {
					if( node == 0 || node->prev == node->pend ) throw invalid_iterator();
					else {
						node = node->prev;
						return *this;
					}
				}
				/**
				 * a operator to check whether two iterators are same (pointing to the same memory).
				 */
				const value_type & operator*() const {
					if( node == 0 || node == node->pend ) throw invalid_iterator();
					return *node->pvalue;
				}
				bool operator==(const iterator &rhs) const {
					return node == rhs.node;
				}
				bool operator==(const const_iterator &rhs) const {
					return node == rhs.node;
				}
				/**
				 * some other operator for iterator.
				 */
				bool operator!=(const iterator &rhs) const {
					return node != rhs.node;
				}
				bool operator!=(const const_iterator &rhs) const {
					return node != rhs.node;
				}

				/**
				 * for the support of it->first. 
				 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
				 */
				const value_type* operator->() const noexcept {
					return node->pvalue;
				}
			};
			/**
			 * TODO two constructors
			 */
			set() {
				pend = (Node*) ::operator new( sizeof(Node) );
				pend->prev = pend->next = pend->lson = pend->rson = pend->pend = pend;
				pend->height = pend->size = 0;
			}
			set(const set &other) {
				if( other.empty() ) {
					pend = new Node;
					pend->prev = pend->next = pend->lson = pend->rson = pend->pend = pend;
					pend->size = pend->height = 0;
					pend->par = 0;
				} else {
					pend = new Node;
					pend->prev = pend->next = pend->lson = pend->rson = pend->pend = pend;
					pend->size = pend->height = 0;
					pend->par = 0;

					size_t n = other.size();
					Node *cur = pend;
					Node *ocur = other.pend;
					for( size_t i = 0; i < n; i++ ) {
						cur->next = new Node;
						cur->next->prev = cur;
						cur->next->pvalue = new value_type(*ocur->next->pvalue);
						cur = cur->next;
						ocur = ocur->next;
					}
					cur->next = pend;
					pend->prev = cur;

					Node **pool = new Node*[n];
					cur = pend->next;
					for( size_t i = 0; i < n; i++ ) {
						pool[i] = cur;
						cur = cur->next;
					}
					pend->lson = build( pool, pend, 0, (int)n-1 );
					delete [] pool;
				}
			}
			/**
			 * TODO assignment operator
			 */
			set & operator=(const set &other) {
				if( this == &other ) return *this;

				clear();
				delete pend;

				new(this) set(other);
				return *this;
			}
			/**
			 * TODO Destructors
			 */
			~set() {
				clear();
				delete pend;
			}
			/**
			 * return a iterator to the beginning
			 */
			iterator begin() {
				return iterator(pend->next);
			}
			const_iterator cbegin() const {
				return const_iterator(pend->next);
			}
			/**
			 * return a iterator to the end
			 * in fact, it returns past-the-end.
			 */
			iterator end() {
				return iterator(pend);
			}
			const_iterator cend() const {
				return const_iterator(pend);
			}
			/**
			 * checks whether the container is empty
			 * return true if empty, otherwise false.
			 */
			bool empty() const {
				return pend->lson == pend;
			}
			/**
			 * returns the number of elements.
			 */
			size_t size() const {
				return pend->lson->size;
			}
			/**
			 * clears the contents
			 */
			void clear() {
				clear(pend->lson);
				pend->lson = pend->rson = pend->prev = pend->next = pend->pend = pend;
			}
			/**
			 * insert an element.
			 * return a pair, the first of the pair is
			 *   the iterator to the new element (or the element that prevented the insertion), 
			 *   the second one is true if insert successfully, or false.
			 */
			pair<iterator, bool> insert(const value_type &value) {
				if( pend->lson == pend ) {
					value_type * pvalue = new value_type(value);
					Node *nd = new Node( pvalue, 1, 1, pend, pend, pend, pend, pend, pend );
					pend->prev = pend->next = pend->lson = nd;
					return pair<iterator,bool>( iterator(nd), true );
				} else {
					pair<Node*,bool> pr = insert( pend->lson, value );
					return pair<iterator,bool>( iterator(pr.first), pr.second );
				}
			}
			/**
			 * erase the element at pos.
			 *
			 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
			 */
			void erase(iterator pos) {
				if( pos.get() == 0 || pos.get()->pend != pend || pos.get() == pend ) throw index_out_of_bound();
				erase( pos.get() );
			}
			/**
			 * Returns the number of elements with key 
			 *   that compares equivalent to the specified argument,
			 *   which is either 1 or 0 
			 *     since this container does not allow duplicates.
			 * The default method of check the equivalence is !(a < b || b > a)
			 */
			size_t count(const Key &key) const {
				return find(pend->lson, key) != pend;
			}
			/**
			 * Finds an element with key equivalent to key.
			 * key value of the element to search for.
			 * Iterator to an element with key equivalent to key.
			 *   If no such element is found, past-the-end (see end()) iterator is returned.
			 */
			iterator find(const Key &key) {
				return iterator(find(pend->lson,key));
			}
			const_iterator find(const Key &key) const {
				return const_iterator(find(pend->lson,key));
			}
			void write( std::ostream &out ) {
				int n = (int)size();
				Node *cur;

				out.write( (char*) &n, sizeof(n) );
				cur = pend->next;
				for( int i = 0; i < n; i++, cur = cur->next ) 
					cur->index = i;
				pend->index = n;
				cur = pend->next;
				for( int i = 0; i < n; i++, cur = cur->next ) {
					out.write( (char*) & cur->par->index, sizeof(int) );
					out.write( (char*) & cur->lson->index, sizeof(int) );
					out.write( (char*) & cur->rson->index, sizeof(int) );
					out.write( (char*) & cur->prev->index, sizeof(int) );
					out.write( (char*) & cur->next->index, sizeof(int) );
					out.write( (char*) & cur->height, sizeof(int) );
					out.write( (char*) & cur->size, sizeof(int) );
					tic::write( out, *cur->pvalue );
				}
			}
			void read( std::istream &in ) {
				int n;
				in.read( (char*) &n, sizeof(int) );

				if( n == 0 ) {
					clear();
				} else {
					Node **pool = new Node*[n+1];
					clear();
					for( int i = 0; i < n; i++ ) {
						pool[i] = new Node;
						in.read( (char*) & pool[i]->par, sizeof(int) );
						in.read( (char*) & pool[i]->lson, sizeof(int) );
						in.read( (char*) & pool[i]->rson, sizeof(int) );
						in.read( (char*) & pool[i]->prev, sizeof(int) );
						in.read( (char*) & pool[i]->next, sizeof(int) );
						in.read( (char*) & pool[i]->height, sizeof(int) );
						in.read( (char*) & pool[i]->size, sizeof(int) );
						pool[i]->pvalue = new value_type;
						tic::read( in, *pool[i]->pvalue );
					}
					pool[n] = pend;
					for( int i = 0; i < n; i++ ) {
						pool[i]->par = pool[(long)pool[i]->par];
						pool[i]->lson = pool[(long)pool[i]->lson];
						pool[i]->rson = pool[(long)pool[i]->rson];
						pool[i]->prev = pool[(long)pool[i]->prev];
						pool[i]->next = pool[(long)pool[i]->next];
						pool[i]->pend = pend;
						if( pool[i]->par == pend ) pend->lson = pool[i];
					}
					pend->prev = pool[n-1];
					pend->next = pool[0];
				}
			}
	};
}


#endif

