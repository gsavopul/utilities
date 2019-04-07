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
//# include <limits>
//# include <type_traits>
//#include <typeinfo>
//#include <cxxabi.h>

//# include <ctime>				// C
//# include <chrono>

# include <boost/filesystem.hpp>
# include <boost/algorithm/string.hpp>
# include <boost/program_options.hpp>
# include <boost/tokenizer.hpp>

//# include <gsavopul.hpp>        // Namespace gsav

//using namespace std;
//using namespace std::chrono;
//using namespace std::rel_ops;
//using namespace std::placeholders;
//using namespace std::literals::complex_literals;
//using namespace std::literals::chrono_literals;


std::wstring titleCase(std::wstring inputString);
void complex_transformation(std::wstring & newFileName);


//int main()
int main(int argc, char * argv[])
{
//    std::locale lgr(std::locale("el_GR.UTF-8"));
//    std::locale::global(lgr);
//    std::cout.imbue(lgr);
//    std::cin.imbue(lgr);
    //============Αρχή κώδικα==================================

	boost::program_options::options_description desc("Options");

	desc.add_options()("help,h", "Print usage information")
						("titlecase,t","Convert filename to title case")
						("uppercase,u","Convert filename to uppercase")
						("lowercase,l","Convert filename to lowercase")
						("firstcap,f","Capitalize first letter, all others in lowercase")
						("complex,c","Complex capitalization scheme."
							"\nInitially prompt for a set of characters for tokenization."
							"\nEach token will be converted separately"
							"\nA map<int,string> will be created to keep defaults"
							"\nIt will correllate the number of tokens to scheme used");

	boost::program_options::variables_map vm;

	try
	{
		boost::program_options::store(
			boost::program_options::command_line_parser(argc,argv)
				.options(desc)
				.style(boost::program_options::command_line_style::unix_style)
				.run(),
			vm);

		boost::program_options::notify(vm);
	}
	catch (boost::program_options::error e)
	{
		std::cout<<e.what()<<"\n"<<desc<<std::endl;
		errno = EINVAL;
		perror("Unsupported Option");
		exit(errno);
	}

	int fileNameOperation=-1;
	if (vm.empty())
	{
		do
		{
			std::wcout<<L"Choose filename transformation: "<<std::endl;
			std::wcout<<L"0 - Abort operation"<<std::endl;
			std::wcout<<L"1 - Convert filenames to title case"<<std::endl;
			std::wcout<<L"2 - Convert filenames to upper case"<<std::endl;
			std::wcout<<L"3 - Convert filenames to lower case"<<std::endl;
			std::wcout<<L"4 - Convert filenames to lower case with the first letter capitalized"<<std::endl;
			std::wcout<<L"5 - Complex operation - Tokenize and capitalize per token"<<std::endl;

			std::wcout<<L"\nEnter your choise: ";
			std::wcin>>fileNameOperation;
		} while (fileNameOperation<-1 || fileNameOperation>6);

		if (fileNameOperation==0) exit(0);
	}
	else if (vm.count("help"))
	{
		std::cout << "\n" << desc << std::endl;
		std::exit(0);
	}


	boost::filesystem::path d=boost::filesystem::current_path();

	boost::filesystem::directory_iterator dit(d);
	boost::filesystem::directory_iterator dif;
	boost::filesystem::path parentPath = dit->path().parent_path();

	std::wstring oldName, newName, fileName, newFileName;

	while (dit!=dif)
	{
		fileName = dit->path().filename().wstring();

		if (vm.count("titlecase") || fileNameOperation==1)
			newFileName = titleCase(fileName);
		else if (vm.count("uppercase") || fileNameOperation==2)
		{
			newFileName=fileName;
			boost::to_upper(newFileName,std::locale(""));
		}
		else if (vm.count("lowercase") || fileNameOperation==3)
		{
			newFileName=fileName;
			boost::to_lower(newFileName,std::locale(""));
		}
		else if (vm.count("firstcap") || fileNameOperation==4)
		{
			newFileName=fileName;
			boost::to_lower(newFileName,std::locale(""));
			std::wstring::size_type idx;
			idx = newFileName.find_first_not_of(L" \t");
			if ( idx != std::wstring::npos )
				newFileName[idx]=std::toupper(newFileName[idx],std::locale(""));
		}
		else if (vm.count("complex") || fileNameOperation==5)
		{
			newFileName=fileName;
			complex_transformation(newFileName);
		}

		boost::filesystem::rename(dit->path(), parentPath.wstring()+L"/"+newFileName);
		++dit;
	}



    //============Τέλος κώδικα=================================
//    std::atexit(calcTime);
	return 0;
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


void complex_transformation(std::wstring & newFileName)
{
	// To be implemented
}
