* 7/4/2019 transformFileNames.cpp
The program now uses boost::program_options, and accepts the following flags:
-h or --help to print usage instructions.
-t or --titlecase to convert filenames to titlecase.
-u or --uppercase to convert filenames to uppercase.
-l or --lowercase to convert filenames to lowercase.
-f or --firstcap to convert filenames to lowercase with a starting capital.
-c or --complex to perform complex conversion (not implemented yet).

* 30/1/2019 space2Underscore.cpp
Added as an option the ability to choose the character to use. The program now
uses boost::program_options, and accepts the following flags:
-c or --character to choose the character into which to convert the spaces found. If this option is ommited, a default value of an underscore is used.
-r or --reverse to reverse the operation and convert the chosen character to space.
-h or --help to print usage instructions.
In windows, it is case insensitive and also accepts /c, /r, /h.

* 1/10/2018 barcodeValidator
Fixed the initialization of digitExp. Minor name changes for the GUI elements.

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
