* 3/7/2018	transformFileNames.cpp
Removed functions upperCase and lowerCase. The program is now using __boost::to_upper()__ 
and __boost::to_lower()__ from header **<boost/algorithm/string.hpp>** for this functionality.
