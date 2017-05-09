/*
 * lib.hpp - include all the lib files and std::string
 */
#ifndef TICKET_LIB_HPP
#define TICKET_LIB_HPP

#include <QString>

typedef QString string;

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;

#include "vector.hpp"
#include "map.hpp"
#include "exceptions.hpp"
#include "utility.hpp"
#include "set.hpp"
#include "time.hpp"
#include "shared_ptr.hpp"
#include "time.hpp"

using tic::Time;
using tic::Date;
using tic::pair;
using tic::set;
using tic::map;
using tic::shared_ptr;
using tic::read;
using tic::write;
using tic::vector;


#endif
