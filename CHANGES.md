* 3/9/2019 transformFileNames.cpp
Minor refactoring. Adopted namespace alias npo for boost::program_options. This shortens function prototypes significantly.
A second namespace alias for boost::program_options::command_line_style has been adopted as well, but is limited to the appropriate function.
Also added new option to print program version. Version number set to #1.

* 21/5/2019 transformFileNames.cpp

Refactoring in smaller program units. The program now uses __boost/predef.h__ macros to identify the OS.
Added an interactive mode, which can be useful if one wants to rename only a few files in a directory and not all.
This mode jumps in with the -i/--interactive flag at the command line. It can also take charge of things if the program
starts with no options at the command line, by specifying a negative integer at the operation chooser menu screen.



* 15/4/2019 space2Underscore.cpp

Refactoring in smaller program units. The program now uses __boost/predef.h__ macros to identify the OS.
Also, instead of set, it uses unordered_set.


* 7/4/2019 transformFileNames.cpp

The program now uses __boost::program_options__, and accepts the following flags:

-h or --help to print usage instructions.

-t or --titlecase to convert filenames to titlecase.

-u or --uppercase to convert filenames to uppercase.

-l or --lowercase to convert filenames to lowercase.

-f or --firstcap to convert filenames to lowercase with a starting capital.

-c or --complex to perform complex conversion (not implemented yet).

In windows, it is case insensitive and also accepts /h, /t, /u, /l, /f, /c.


* 30/1/2019 space2Underscore.cpp

Added as an option the ability to choose the character to use. The program now
uses __boost::program_options__, and accepts the following flags:

-c or --character to choose the character into which to convert the spaces found.
If this option is ommited, a default value of an underscore is used.

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
