* 26/9/2018 space2Underscore.cpp
Added the inverse procedure as a command line option. If the program is
execuded from the command line with the option -r or -R, it will convert
underscores to spaces.

* 23/9/2018 transformFileNames.cpp
Changed regex for title case. The new expression takes into account the possibility
that an optional punctuation mark (eg parenthesis) may appear right after the space,
with letters following it. In such occasion, the first of these letters should be in
upper case. In the previous incarnation of the program, all letters would have
been in lower case.

* 3/7/2018	transformFileNames.cpp
Removed functions upperCase and lowerCase. The program is now using __boost::to_upper()__
and __boost::to_lower()__ from header **<boost/algorithm/string.hpp>** for this functionality.
