# This repository contains various small utilities

## List of utilities
space2Underscore.cpp - When executed in a directory, converts space characters in all filenames to underscores. Non recursive.
transformFileNames.cpp - When executed in a directory converts all filenames to title/upper/lower case. Also non recursive.

## Description
space2Underscore.cpp - Uses Boost filesystem. Can be compiled using the run script with the -b flag.
transformFileNames.cpp - Uses Boost filesystem. Compilation as above. Should work fine with UTF-8 filesystems but may require changes for others due to codecvt_utf8.
