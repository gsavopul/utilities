# This repository contains various small utilities

## List of utilities
- space2Underscore.cpp

- transformFileNames.cpp

- barcodeValidator

## Description
**space2Underscore.cpp**

When executed in a directory, this small program converts every white character in the filenames to an underscore. The process is non recursive.
It uses _Boost filesystem_, _Boost string algorithms_ and _Boost program options_. _Boost predef_ macros are used for the identification of the
operating system. Accepts the flags -h(elp), -r(everse) and -c(haracter) + value.
One way to compile and run it is through the run script with the -b flag.

**transformFileNames.cpp**

When executed in a directory this program converts all filenames to title/upper/lower case. This process is also non recursive,
uses _Boost program options_, _Boost filesystem_, but works with wide strings and locale dependent functions in order to perform
the task. Compilation as above. In case of __a capital letter corresponding to more than one small letter in the locale__ note the following:

- the transformation lower->upper->lower might produce a "different" filename that the original (eg ς->Σ->σ).

- the transformation upper->lower might produce "grammatically incorrect" filenames (eg Σ->σ instead of ς at the end of a word).

**barcodeValidator**

This directory contains a small Qt project for validating barcodes (specifically, 12-digit UPC or 13-digit EAN). Validation is being handled using QValidator and QRegExp.
