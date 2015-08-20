#include "..\src\micpp.h"

//hello_world
namespace hello_world
{
	//print
	FUNCTION0(print)
	{
		LOCAL(str)[] = {'h', 'e', 'l', 'l', 'o', ' ',
						'w', 'o', 'r', 'l', 'd', '!', '!', '!', '\0'};
		
		micpp::print_string(str, '\n');
		return 0;
	}
};
