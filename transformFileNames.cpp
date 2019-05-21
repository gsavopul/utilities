// ------------------------------------------------------------------  io
//# include <iosfwd>
//# include <istream>
//# include <ostream>
# include <iostream>
# include <fstream>
//# include <sstream>
//# include <streambuf>
# include <iomanip>

//# include <cstdio>			// C
//# include <cstdlib>			// C
//# include <cstddef>			// C
//# include <cmath>				// C
//# include <complex>

// ------------------------------------------------------------------  strings
# include <string>
# include <regex>
//# include <cstring>			// C
//# include <cctype>			// C

// ------------------------------------------------------------------  containers
//# include <vector>
//# include <deque>
//# include <list>
//# include <set>
//# include <map>
//# include <unordered_set>
//# include <unordered_map>

//# include <stack>
//# include <que>
//# include <priority_que>
//# include <forward_list>
//# include <bitset>
//# include <complex>

//  -----------------------------------------------------------------  algorithms
//# include <algorithm>
//# include <iterator>
//# include <utility>
//# include <functional>
//# include <numeric>
//# include <random>

// ------------------------------------------------------------------  multithreading
# include <thread>
//# include <future>
//# include <atomic>
//# include <mutex>
//# include <condition_variable>

// ------------------------------------------------------------------  exceptions and error handling
//#include <exception>
//#include <stdexcept>
//#include <system_error>
//#include <ios>
//#include <typeinfo>
#include <cerrno>              // C - χειρισμός σφαλμάτων συστήματος

// ------------------------------------------------------------------  system calls
//# include <syscall.h>			// System calls
//# include <windows.h>			// System calls for windows

// ------------------------------------------------------------------  localization
# include <locale>
//# include <codecvt>

// ------------------------------------------------------------------  various
//# include <memory>
//# include <new>

//# include <climits>			// C
//# include <cfloat>			// C
# include <limits>
//# include <type_traits>
//#include <typeinfo>
//#include <cxxabi.h>

//# include <ctime>				// C
//# include <chrono>

# include <boost/filesystem.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/program_options.hpp>
# include <boost/tokenizer.hpp>
# include <boost/predef.h>
//# include <gsavopul.hpp>        // Namespace gsav

//using namespace std;
//using namespace std::chrono;
//using namespace std::rel_ops;
//using namespace std::placeholders;
//using namespace std::literals::complex_literals;
//using namespace std::literals::chrono_literals;

int setup_options(boost::program_options::variables_map &vm, int argc, char * argv[]);
void define_options(boost::program_options::options_description &desc);
int define_style(void);
void parse_options(boost::program_options::options_description &desc, boost::program_options::variables_map &vm, int argc, char * argv[]);
void choose_operation(int &fileNameOperation);
std::wstring titleCase(std::wstring inputString);
void complex_transformation(std::wstring & newFileName);
void loop_over_files(int fileNameOperation, boost::program_options::variables_map vm);
std::wstring convertFileName(int fileNameOperation, boost::program_options::variables_map vm, std::wstring fileName);
bool confirmChange(std::wstring fileName, std::wstring newFileName);
bool checkNoOp(int fileNameOperation, boost::program_options::variables_map vm);


//int main()
int main(int argc, char * argv[])
{
    std::locale def_loc(std::locale(""));
    std::locale::global(def_loc);
//    std::cout.imbue(lgr);
//    std::cin.imbue(lgr);
    //============Αρχή κώδικα==================================

	boost::program_options::variables_map vm;
	int fileNameOperation = std::numeric_limits<int>::max();

	if (argc != 1)
	{
		int status = setup_options(vm,argc,argv);
		if (status != 0) return status;
	}
	else
	{
		choose_operation(fileNameOperation);
		if (fileNameOperation==0) exit(0);
	}

	if (!checkNoOp(fileNameOperation,vm))
		loop_over_files(fileNameOperation,vm);


    //============Τέλος κώδικα=================================
//    std::atexit(calcTime);
	return 0;
}


int setup_options(boost::program_options::variables_map &vm, int argc, char * argv[])
{
	boost::program_options::options_description desc("Options");

	define_options(desc);
	try
	{
		parse_options(desc,vm,argc,argv);
		if (vm.count("help"))
		{
			std::cout << "USAGE: " << argv[0] << '\n' << desc << '\n';
			exit(0);
		}
		return 0;
	}
	catch (boost::program_options::error &e)
	{
		std::cerr << e.what() << '\n' << "USAGE: " << argv[0] << '\n' << desc << '\n';
		return EXIT_FAILURE;
	}
}


void define_options(boost::program_options::options_description &desc)
{
//	This subroutine defines the options that will be recognised by this program
	desc.add_options()
		("help,h", "Print usage information")
		("interactive,i", "Confirm user's permission for every proposed filename change")
		("titlecase,t","Convert filename to title case")
		("uppercase,u","Convert filename to uppercase")
		("lowercase,l","Convert filename to lowercase")
		("firstcap,f","Capitalize first letter, all others in lowercase")
		("complex,c","Complex capitalization scheme."
			"\nInitially prompt for a set of characters for tokenization."
			"\nEach token will be converted separately"
			"\nA map<int,string> will be created to keep defaults"
			"\nIt will correllate the number of tokens to scheme used");
}


int define_style(void)
{
//	This subroutine defines the command line style
	int style;
	if (BOOST_OS_UNIX)
		style = boost::program_options::command_line_style::unix_style;
	else if (BOOST_OS_WINDOWS)
		style = boost::program_options::command_line_style::unix_style |
				boost::program_options::command_line_style::case_insensitive |
				boost::program_options::command_line_style::allow_slash_for_short;

	return style;
}


void parse_options(boost::program_options::options_description &desc, boost::program_options::variables_map &vm, int argc, char * argv[])
{
	int style =	define_style();

	boost::program_options::store(
		boost::program_options::command_line_parser(argc,argv)
			.options(desc)
			.style(style)
			.run(),
		vm);

	boost::program_options::notify(vm);
}


void choose_operation(int &fileNameOperation)
{
	std::vector<std::string> v{"titlecase","uppercase","lowercase","firstcap","complex"};
	do
	{
		std::wcout<<L"Choose filename transformation: "<<std::endl;
		std::wcout<<L"0 - Abort operation"<<std::endl;
		std::wcout<<L"1 - Convert filenames to title case"<<std::endl;
		std::wcout<<L"2 - Convert filenames to upper case"<<std::endl;
		std::wcout<<L"3 - Convert filenames to lower case"<<std::endl;
		std::wcout<<L"4 - Convert filenames to lower case with the first letter capitalized"<<std::endl;
		std::wcout<<L"5 - Complex operation - Tokenize and capitalize per token"<<std::endl;

		std::wcout<<L"\nInsert negative number for interactive mode. Enter your choise: ";
		std::wcin>>fileNameOperation;
	} while (fileNameOperation<-6 || fileNameOperation>6);
}


std::wstring titleCase(std::wstring inputString)
{
//  The function converts the input string to titlecase

    boost::to_lower(inputString,std::locale(""));
   	std::wregex reg(L"[[:space:]]+([[:punct:]]+)?");

    std::wsregex_iterator ri(inputString.begin(),inputString.end(),reg);
   	std::wsregex_iterator nd;

	if (regex_search(inputString, reg))
	{
		auto x = ri->prefix().first;

		while (ri != nd)
		{
			std::wstring::size_type idx = distance(x, ri->suffix().first);
			inputString[idx] = std::toupper(inputString[idx], std::locale(""));
			++ri;
		}
	}

   	inputString[0] = std::toupper(inputString[0],std::locale(""));
	return inputString;
}


void loop_over_files(int fileNameOperation, boost::program_options::variables_map vm)
{
//	This subroutine loops over the files of the current directory and renames the files
	boost::filesystem::path d=boost::filesystem::current_path();
	boost::filesystem::directory_iterator dit(d);
	boost::filesystem::directory_iterator dif;
	boost::filesystem::path parentPath = dit->path().parent_path();

	std::wstring fileName, newFileName;
	bool confirm=true;

	while (dit!=dif)
	{
		fileName = dit->path().filename().wstring();
		newFileName = convertFileName(fileNameOperation, vm, fileName);
		if (fileNameOperation<0 || vm.count("interactive"))
			confirm = confirmChange(fileName, newFileName);
		if (confirm)
			boost::filesystem::rename(dit->path(), parentPath.wstring()+L"/"+newFileName);
		++dit;
	}

}


std::wstring convertFileName(int fileNameOperation, boost::program_options::variables_map vm, std::wstring fileName)
{
//	This subroutine transforms the filename
	std::wstring newFileName;

	if (vm.count("titlecase") || abs(fileNameOperation) == 1)
		newFileName = titleCase(fileName);
	else if (vm.count("uppercase") || abs(fileNameOperation) == 2)
		newFileName = boost::to_upper_copy(fileName,std::locale(""));
	else if (vm.count("lowercase") || abs(fileNameOperation) == 3)
		newFileName = boost::to_lower_copy(fileName,std::locale(""));
	else if (vm.count("firstcap") || abs(fileNameOperation) == 4)
	{
		newFileName=fileName;
		boost::to_lower(newFileName,std::locale(""));
		std::wstring::size_type idx;
		idx = newFileName.find_first_not_of(L" \t");
		if ( idx != std::wstring::npos )
			newFileName[idx]=std::toupper(newFileName[idx],std::locale(""));
	}
	else if (vm.count("complex") || abs(fileNameOperation) == 5)
	{
		newFileName=fileName;
		complex_transformation(newFileName);
	}
	else
		return fileName;

	return newFileName;
}


bool confirmChange(std::wstring fileName, std::wstring newFileName)
{
//	This subroutine presents the impending filename change and asks for user input before commiting it
//	Relevant only in interactive mode.
	bool confirm;
	std::wstring response;

	do
	{
		std::wcout<<L"\nOriginal filename is: "<<fileName<<std::endl;
		std::wcout<<L"It will be converted to: "<<newFileName<<std::endl;
		std::wcout<<L"Proceed with the renaming? (Y/N) [default action is N]: ";
		std::getline(std::wcin,response);
	} while (response!=L"N" && response!=L"n" && response!=L"Y" && response!=L"y" && response!=L"\0");

	boost::to_upper(response,std::locale(""));
	confirm = ( !(response[0] - L'Y') ? true : false);

	return confirm;
}


bool checkNoOp(int fileNameOperation, boost::program_options::variables_map vm)
{
//	This subroutine checks if filename altering options have been given
//	If not, there is no reason to loop over the files.

	if (fileNameOperation != std::numeric_limits<int>::max())
		return false;

	if (vm.count("titlecase") || vm.count("uppercase") || vm.count("lowercase") || vm.count("firstcap") || vm.count("complex") )
		return false;

	return true;
}


void complex_transformation(std::wstring & newFileName)
{
	// To be implemented
}
