/*
reference
http://www.boost.org/doc/libs/1_56_0/libs/log/example/doc/tutorial_file.cpp
http://lists.boost.org/boost-users/att-79396/test_logging.cpp
*/

//boost log headers
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

//additional headers
#include <string>
using namespace std;

void log_init(const string &log_file)
{
	logging::add_file_log
	(
		keywords::file_name = log_file,
		keywords::format = "%TimeStamp% %Message%"
	);
	logging::add_common_attributes();
}

//function name macro, __FUNCTION__, __func__
#define MY_LOG(lg) \
	BOOST_LOG(lg) << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << ": "

int main(int argc, char *argv[])
{
	src::logger lg;
	string log_file = argv[0];
	log_init(log_file.substr(0, log_file.rfind('.')) + ".log");

	MY_LOG(lg) << "A trace severity message";
	MY_LOG(lg) << "A debug severity message";
	MY_LOG(lg) << "An informational severity message";
	MY_LOG(lg) << "A warning severity message";
	MY_LOG(lg) << "An error severity message";
	MY_LOG(lg) << "A fatal severity message";

	return 0;
}


/*
Visual Studio 2013
$ bootstrap
$ b2 toolset=msvc-12.0 debug
$ b2 toolset=msvc-12.0 release

Release Output
2014-Sep-06 10:49:54.334622 Source.cpp 47 main: A trace severity message
2014-Sep-06 10:49:54.350222 Source.cpp 48 main: A debug severity message
2014-Sep-06 10:49:54.350222 Source.cpp 49 main: An informational severity message
2014-Sep-06 10:49:54.350222 Source.cpp 50 main: A warning severity message
2014-Sep-06 10:49:54.350222 Source.cpp 51 main: An error severity message
2014-Sep-06 10:49:54.350222 Source.cpp 52 main: A fatal severity message

Debug Output
2014-Sep-06 10:51:07.358350 c:\users\Guest\documents\visual studio 2013\projects\consoleapplication1\consoleapplication1\source.cpp 47 main: A trace severity message
2014-Sep-06 10:51:07.358350 c:\users\Guest\documents\visual studio 2013\projects\consoleapplication1\consoleapplication1\source.cpp 48 main: A debug severity message
2014-Sep-06 10:51:07.358350 c:\users\Guest\documents\visual studio 2013\projects\consoleapplication1\consoleapplication1\source.cpp 49 main: An informational severity message
2014-Sep-06 10:51:07.358350 c:\users\Guest\documents\visual studio 2013\projects\consoleapplication1\consoleapplication1\source.cpp 50 main: A warning severity message
2014-Sep-06 10:51:07.358350 c:\users\Guest\documents\visual studio 2013\projects\consoleapplication1\consoleapplication1\source.cpp 51 main: An error severity message
2014-Sep-06 10:51:07.358350 c:\users\Guest\documents\visual studio 2013\projects\consoleapplication1\consoleapplication1\source.cpp 52 main: A fatal severity message
*/
