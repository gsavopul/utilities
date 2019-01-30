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
# include <set>
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

# include <boost/filesystem.hpp>
# include <boost/program_options.hpp>

//# include <gsavopul.hpp>        // Namespace gsav

//using namespace std;
//using namespace std::chrono;
//using namespace std::rel_ops;
//using namespace std::placeholders;
//using namespace std::literals::complex_literals;
//using namespace std::literals::chrono_literals;


void character_check(char ch, std::string &str, std::string &str_reverse, std::set<char> invalids);

//int main()
int main(int argc, char * argv[])
{
//    std::locale lgr(std::locale("el_GR.UTF-8"));
//    std::locale::global(lgr);
//    std::cout.imbue(lgr);
//    std::cin.imbue(lgr);
    //============Αρχή κώδικα==================================

	boost::program_options::options_description opt("Options");

	opt.add_options()
		("character,c",boost::program_options::value<char>()->default_value('_'),
		"Converts space to specified character (by default an underscore). "
		"Note that the characters ?,<,>,\\,*,|,\',\",&,(,),{,},;,` should be escaped at the command line in UNIX. "
		"\nFor example: space2Underscore -c \\?. "
		"\nSimilarly, characters ^ and & should be escaped at the command line in Windows. "
		"\nFor example: space2Underscore -c^^")
		("reverse,r","Converts specified character (by default an underscore) to space")
		("help,h","Prints usage instructions");

	boost::program_options::variables_map vm;
	boost::filesystem::path d=boost::filesystem::current_path();

	int cmd_style;
	if (d.root_name().empty())
		cmd_style = boost::program_options::command_line_style::unix_style;
	else
	{
		cmd_style = boost::program_options::command_line_style::allow_slash_for_short
					| boost::program_options::command_line_style::allow_dash_for_short
					| boost::program_options::command_line_style::case_insensitive
					| boost::program_options::command_line_style::allow_short
 					| boost::program_options::command_line_style::allow_long
					| boost::program_options::command_line_style::short_allow_next
					| boost::program_options::command_line_style::long_allow_next
					| boost::program_options::command_line_style::short_allow_adjacent
					| boost::program_options::command_line_style::long_allow_adjacent
					| boost::program_options::command_line_style::allow_sticky;
	}


	try
	{
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv)
		.options(opt)
		.style(cmd_style)
		.run(), vm);

		boost::program_options::notify(vm);

		if (vm.count("help"))
		{
			std::cout << "USAGE: " << argv[0] << '\n' << opt << '\n';
			return 0;
		}
	}
	catch (boost::program_options::error& poe)
	{
		std::cerr << poe.what() << '\n' << "USAGE: " << argv[0] << '\n' << opt << '\n';
		return EXIT_FAILURE;
	}

	bool invFlag;
	if (vm.count("reverse"))
		invFlag=true;
	else
		invFlag=false;

	char ch=vm["character"].as<char>();
//	Special regex symbols such as +, ? etc...
	std::string str,str_reverse;
	std::set<char> windows_invalids{':', '/', '?', '<', '>', '\\', '*', '|', '\"'};
	std::set<char> unix_invalids{'/'};

	if (d.root_name().empty())
		character_check(ch,str,str_reverse,unix_invalids);
	else
		character_check(ch,str,str_reverse,windows_invalids);


	boost::filesystem::directory_iterator dit(d);
	boost::filesystem::directory_iterator dif;
	boost::filesystem::path parentPath = dit->path().parent_path();

	std::string oldName, newName, fileName, newFileName;

	while (dit!=dif)
	{
		fileName = dit->path().filename().string();
		if (!invFlag)
		{
			if ( regex_search(fileName,std::regex("[[:blank:]]")) )
			{
				newFileName = regex_replace(fileName,std::regex("[[:blank:]]"),str);
				boost::filesystem::rename(dit->path(), parentPath.string()+"/"+newFileName);
			}
			++dit;
		}
		else
		{
			try
			{
				if ( regex_search(fileName,std::regex(str_reverse)) )
				{
					newFileName = regex_replace(fileName,std::regex(str_reverse)," ");
					boost::filesystem::rename(dit->path(), parentPath.string()+"/"+newFileName);
				}
			}
			catch (std::exception e)
			{
				std::cout<<"error !"<<e.what()<<std::endl;
			}
			++dit;
		}
	}

    //============Τέλος κώδικα=================================
//    std::atexit(calcTime);
	return 0;
}


void character_check(char ch, std::string &str, std::string &str_reverse, std::set<char> invalids)
{
	std::set<char> specials{':', '/', '+', '^', '$', '?', '<', '>', '\\', '*', '|', '\"', '(', ')', '{', '}', '[', ']', '.'};

	if ( specials.find(ch) != specials.end() )
		if ( invalids.find(ch) != invalids.end() )
		{
			std::cout<<"Invalid character detected! Aborting operation!\n";
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

