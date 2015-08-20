#include <conio.h>
#include "..\src\micpp.h"

#include "hello_world.h"

//main
int main(int argc, char** argv)
{
	//compiler hello_world.h
	micpp* cpp_hello_world = micpp::Compiler("hello_world.h", false);
	
	//native call hello_world::print
	hello_world::print();
	
	//micpp call hello_world::print
	micpp::Call(cpp_hello_world->Function("print"));
	
	//micpp call hello_world::print (other style)
	micpp::Call(micpp::Find("hello_world")->Function("print"));
	
	//destroy
	micpp::Destroy(cpp_hello_world);
	
	getch();
	return 0;
}
