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

//# include <gsavopul.hpp>        // Namespace gsav

//using namespace std;
//using namespace std::chrono;
//using namespace std::rel_ops;
//using namespace std::placeholders;
//using namespace std::literals::complex_literals;
//using namespace std::literals::chrono_literals;

//  Η συνάρτηση μετατρέπει όλους τους χαρακτήρες μιας συμβολοσειράς σε κεφαλαίους
std::string upperCase(std::string inputString)
{
	std::wstring ws;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cnv;

	ws=cnv.from_bytes(inputString);

    for (auto &stringCharacter: ws)
        stringCharacter=std::toupper(stringCharacter,std::locale(""));

    return cnv.to_bytes(ws);
}


//  Η συνάρτηση μετατρέπει όλους τους χαρακτήρες μιας συμβολοσειράς σε πεζούς
std::string lowerCase(std::string inputString)
{
	std::wstring ws;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cnv;

	ws=cnv.from_bytes(inputString);

    for (auto &stringCharacter: ws)
        stringCharacter=std::tolower(stringCharacter,std::locale(""));

    return cnv.to_bytes(ws);
}


//  Η συνάρτηση μετατρέπει όλους τους χαρακτήρες μιας συμβολοσειράς σε χαρακτήρες τίτλων
std::string titleCase(std::string inputString)
{

    inputString = lowerCase(inputString);

	std::wstring ws;
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cnv;

	ws=cnv.from_bytes(inputString);
    std::wregex reg(L"[[:space:]]+");

    std::wsregex_iterator ri(ws.begin(),ws.end(),reg);
    std::wsregex_iterator nd;
    auto x = ri->prefix().first;

    while(ri!=nd)
    {
        std::wstring::size_type idx=distance(x,ri->suffix().first);
        ws[idx] = std::toupper(ws[idx],std::locale(""));
        ++ri;
    }

    ws[0] = std::toupper(ws[0],std::locale(""));
    return cnv.to_bytes(ws);
}



int main()
//int main(int argc, char * argv[])
{
//    std::locale lgr(std::locale("el_GR.UTF-8"));
//    std::locale::global(lgr);
//    std::cout.imbue(lgr);
//    std::cin.imbue(lgr);
    //============Αρχή κώδικα==================================

	boost::filesystem::path d=boost::filesystem::current_path();

	boost::filesystem::directory_iterator dit(d);
	boost::filesystem::directory_iterator dif;
	boost::filesystem::path parentPath = dit->path().parent_path();

	std::string oldName, newName, fileName, newFileName;

	int fileNameOperation;
	do
	{
		std::cout<<"Choose filename transformation: "<<std::endl;
		std::cout<<"0 - Abort operation"<<std::endl;
		std::cout<<"1 - Convert filenames to title case"<<std::endl;
		std::cout<<"2 - Convert filenames to upper case"<<std::endl;
		std::cout<<"3 - Convert filenames to lower case"<<std::endl;

		std::cout<<"\nEnter your choise: ";
		std::cin>>fileNameOperation;
	} while (fileNameOperation<-1 || fileNameOperation>4);

	if (fileNameOperation==0) exit(0);
	while (dit!=dif)
	{
		fileName = dit->path().filename().string();
		switch (fileNameOperation)
		{
			case 1:
				newFileName = titleCase(fileName);
				break;
			case 2:
				newFileName = upperCase(fileName);
				break;
			case 3:
				newFileName = lowerCase(fileName);
				break;
		}
		boost::filesystem::rename(dit->path(), parentPath.string()+"/"+newFileName);
		++dit;
	}

    //============Τέλος κώδικα=================================
//    std::atexit(calcTime);
	return 0;
}
