#pragma once
#include <stdlib.h>
#include <list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <fstream>
#include <thread>
#include <chrono>

#include <boost/shared_ptr.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/shared_array.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/lockfree/queue.hpp>

#include "sqlite3.h"
#include "getopt.h"
#include "gosthash.h"

#include "gosthash.h"
#include "gosthash2012.h"
#include "gost89.h"
#include "hashdata.h"
