#include "..\src\micpp.h"

//hello_world
namespace hello_world
{
	//print
	FUNCTION0(print)
	{
		micpp::print_string("hello world!!!\n");
		return 0;
	}
};
