// ------------------------------------------------------------------  io
//# include <iosfwd>
//# include <istream>
//# include <ostream>
# include <iostream>
//# include <fstream>
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
# include <unordered_set>
//# include <unordered_map>

//# include <stack>
//# include <que>
//# include <priority_que>
//# include <forward_list>
//# include <bitset>
//# include <complex>

//  -----------------------------------------------------------------  algorithms
//# include <algorithm>
# include <iterator>
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
//#include <cerrno>              // C - χειρισμός σφαλμάτων συστήματος

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

# include <boost/predef.h>
# include <boost/filesystem.hpp>
# include <boost/program_options.hpp>

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
std::unordered_set<char> define_invalids(void);
void character_check(char ch, std::string &str, std::string &str_reverse, std::unordered_set<char> invalids);
void loop_over_files(std::string str, std::regex reg);

//int main()
int main(int argc, char * argv[])
{
//    std::locale lgr(std::locale("el_GR.UTF-8"));
//    std::locale::global(lgr);
//    std::cout.imbue(lgr);
//    std::cin.imbue(lgr);
    //============Αρχή κώδικα==================================

	boost::program_options::variables_map vm;
	int status = setup_options(vm,argc,argv);
	if (status != 0) return status;

	char ch=vm["character"].as<char>();

	std::unordered_set<char> invalids = define_invalids();
	std::string str, str_reverse;
	character_check(ch,str,str_reverse,invalids);

	if (!vm.count("reverse"))
		loop_over_files(str, std::regex("[[:blank:]]"));
	else
		loop_over_files(" ", std::regex(str_reverse));


    //============Τέλος κώδικα=================================
//    std::atexit(calcTime);
	return 0;
}


int setup_options(boost::program_options::variables_map &vm, int argc, char * argv[])
{
//	This subroutine sets up the options for the program and returns the map that contains them.
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
	catch (boost::program_options::error e)
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
		("character,c", boost::program_options::value<char>()->default_value('_'),
		"Converts space to specified character (by default an underscore). ")
		("reverse,r","Converts specified character (by default an underscore) to space."
		"\n\nNote that at the UNIX command line, the characters: ~,`,&,*,(,),;,\',\",\\,|,<,>,?"
		" should be escaped. "
		"\nFor example: space2Underscore -c \\?. "
		"\n\nSimilarly, at the Windows command line, characters ^ and & should be escaped. "
		"\nFor example: space2Underscore -c^^");
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
//	This subroutine runs the parser and fills the map that contains the options.
	int style =	define_style();

	boost::program_options::store(
		boost::program_options::command_line_parser(argc,argv)
			.options(desc)
			.style(style)
			.run(),
		vm);

	boost::program_options::notify(vm);
}


std::unordered_set<char> define_invalids()
{
//	This subroutine defines illegal characters that cannot be part of a filename in various systems.
	std::unordered_set<char> invalids;
	if (BOOST_OS_WINDOWS)
		invalids.insert({'*', ':', '\"', '\\', '|', '<', '>', '/', '?'});
	else if (BOOST_OS_UNIX)
		invalids.insert('/');

	return invalids;
}


void character_check(char ch, std::string &str, std::string &str_reverse, std::unordered_set<char> invalids)
{
//	This subroutine checks the character given to find out if it requires additional processing or if it is an illegal one.
	std::unordered_set<char> specials{':', '/', '+', '^', '$', '?', '<', '>', '\\', '*', '|', '\"', '(', ')', '{', '}', '[', ']', '.'};

	if ( specials.find(ch) != specials.end() )
		if ( invalids.find(ch) != invalids.end() )
		{
			std::cerr<<"The character(s): ";
			std::copy(invalids.begin(),invalids.end(),std::ostream_iterator<char>(std::cerr," "));
			std::cerr<<"\ncannot be part of a filename in this operating system! Aborting operation!\n";

			exit(EXIT_FAILURE);
		}
		else
		{
			str=std::string(1,ch);
			str_reverse=std::string(1,'\\') + std::string(1,ch);
		}
	else
		str=str_reverse=std::string(1,ch);
}


void loop_over_files(std::string str, std::regex reg)
{
//	This subroutine loops over the files and renames them
	boost::filesystem::path d=boost::filesystem::current_path();
	boost::filesystem::directory_iterator dit(d);
	boost::filesystem::directory_iterator dif;
	boost::filesystem::path parentPath = dit->path().parent_path();

	std::string oldName, newName, fileName, newFileName;

	while (dit!=dif)
	{
		fileName = dit->path().filename().string();
		try
		{
			if ( regex_search(fileName,reg) )
			{
				newFileName = regex_replace(fileName,reg,str);
				boost::filesystem::rename(dit->path(), parentPath.string()+"/"+newFileName);
			}
		}
		catch (std::exception e)
		{
			std::cerr<<e.what()<<std::endl;
		}
		++dit;
	}
}

