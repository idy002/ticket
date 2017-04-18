/*
 * exceptions.hpp - declare some exceptions
 */
#ifndef TICKET_EXCEPTIONS_H
#define TICKET_EXCEPTIONS_H

#include <cstddef>
#include <cstring>
#include <string>

namespace tic {
	class exception {
		protected:
			const std::string variant = "";
			std::string detail = "";
		public:
			exception() {}
			exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
			virtual std::string what() {
				return variant + " " + detail;
			}
	};

	/**
	 *  * TODO
	 *   * Please complete them.
	 *    */
	class index_out_of_bound : public exception {
		/* __________________________ */
	};

	class runtime_error : public exception {
		/* __________________________ */
	};

	class invalid_iterator : public exception {
		/* __________________________ */
	};

	class container_is_empty : public exception {
		/* __________________________ */
	};

	class dereference_empty_pointer : public exception {
	};
}

#endif
