//MiCpp project - micpp.h
//Copyright (c) 2012 Mido - exmido@gamil.com
/*
MIT open source licence:

Copyright (c) 2012 Mido

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MICPP_H
#define MICPP_H

#include <stdio.h>

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <map>

#ifdef _64BIT
	typedef long long INT_T;
#else
	typedef int INT_T;
#endif

#define ISCPP				1
#define MICPP_MAX_PATH		260

#define GLOBAL(name)		static micpp::variable name
#define INDEX(name)			static const int name
#define LOCAL(name)			micpp::variable name

#define ISDEF()				true
#define CPPFUN(fun)			fun
#define MIFUN(fun)			(*(cppNode*)(fun).ptr)

#define FUNCTION0(name)																			inline static micpp::variable name()
#define FUNCTION1(name, param0)																	inline static micpp::variable name(micpp::variable param0)
#define FUNCTION2(name, param0, param1)															inline static micpp::variable name(micpp::variable param0, micpp::variable param1)
#define FUNCTION3(name, param0, param1, param2)													inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2)
#define FUNCTION4(name, param0, param1, param2, param3)											inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3)
#define FUNCTION5(name, param0, param1, param2, param3, param4)									inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4)
#define FUNCTION6(name, param0, param1, param2, param3, param4, param5)							inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5)
#define FUNCTION7(name, param0, param1, param2, param3, param4, param5, param6)					inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5, micpp::variable param6)
#define FUNCTION8(name, param0, param1, param2, param3, param4, param5, param6, param7)			inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5, micpp::variable param6, micpp::variable param7)
#define FUNCTION9(name, param0, param1, param2, param3, param4, param5, param6, param7, param8)	inline static micpp::variable name(micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5, micpp::variable param6, micpp::variable param7, micpp::variable param8)

/*
//<start>			-> "namespace" <name> "{" (<global>)* (<function>)* "};"

//<global>			-> ( "GLOBAL(" | "INDEX(" ) <name> ")" (("=" <expression>) | ("[<expression>]" ("={" <expression> ("," <expression>)* "}")?) | ("[]={" <expression> ("," <expression>)* "}"))? ";"
//<local>			-> ( "LOCAL(" ) <name> ")" (("=" <expression>) | ("[<expression>]" ("={" <expression> ("," <expression>)* "}")?) | ("[]={" <expression> ("," <expression>)* "}"))? ";"
//<function>		-> "FUNCTION0(" <name> ")" (";" | <block>)
//						| "FUNCTION1(" <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION2(" <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION3(" <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION4(" <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION5(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION6(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION7(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION8(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
//						| "FUNCTION9(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)

//<if>				-> "if(" <expression> ")" <block> | <line> ("else if(" <expression> ")" <block> | <line>)* ("else" <block> | <line>)?
//<for>				-> "for(" (<global> | <locla> | (<expression>)? ";") (<expression>) ";" <expression> ")" <block> | <line>

//<block>			-> "{" (<block> | <global> | <local> | (("return")? <expression> ";") | <if> | <for> | "break" | "continue")* "}"
//<line>			-> ("return")? <expression> ";") | <if> | <for> | break | continue

//<expression>		-> <layer0> ("=" <layer0>)*
//<layer0>			-> <layer1> ("||" <layer1>)*
//<layer1>			-> <layer2> ("&&" <layer2>)*
//<layer2>			-> <layer3> (("==" | "!=") <layer3>)*
//<layer3>			-> <layer4> (("<" | "<=" | ">" | ">=") <layer4>)*
//<layer4>			-> <layer5> (("+" | "-") <layer5>)*
//<layer5>			-> <layer6> (("*" | "/" | "%") <layer6>)*
//<layer6>			-> ("!" | "+" | "-" | "&") <layer6>
//					-> "(" <expression> ")"
//					-> (number("." number "f")?) | ("0x"number)
//					-> ("L") "'" ("\")? <char> "'"
//					-> ((name) "::" )name?(( "(" (<expression> ("," <expression>)*) ")") | ("[" <expression> "]"))*
*/

class cppNode;
class CompilerInfo;

//micpp
class micpp
{
public:
	friend class cppNative;
	friend class cppVariable;
	friend class cppLocal;
	friend class cppGlobal;
	friend class cppOperator;
	friend class cppBlock;
	friend class cppFunction;

	//variable
	class variable
	{
	public:
		typedef variable (*VAR_FUN_PARAM0)();
		typedef variable (*VAR_FUN_PARAM1)(variable);
		typedef variable (*VAR_FUN_PARAM2)(variable, variable);
		typedef variable (*VAR_FUN_PARAM3)(variable, variable, variable);
		typedef variable (*VAR_FUN_PARAM4)(variable, variable, variable, variable);
		typedef variable (*VAR_FUN_PARAM5)(variable, variable, variable, variable, variable);
		typedef variable (*VAR_FUN_PARAM6)(variable, variable, variable, variable, variable, variable);
		typedef variable (*VAR_FUN_PARAM7)(variable, variable, variable, variable, variable, variable, variable);
		typedef variable (*VAR_FUN_PARAM8)(variable, variable, variable, variable, variable, variable, variable, variable);
		typedef variable (*VAR_FUN_PARAM9)(variable, variable, variable, variable, variable, variable, variable, variable, variable);

		union
		{
			float			val;
			variable*		ptr;
			VAR_FUN_PARAM0	fun0;
			VAR_FUN_PARAM1	fun1;
			VAR_FUN_PARAM2	fun2;
			VAR_FUN_PARAM3	fun3;
			VAR_FUN_PARAM4	fun4;
			VAR_FUN_PARAM5	fun5;
			VAR_FUN_PARAM6	fun6;
			VAR_FUN_PARAM7	fun7;
			VAR_FUN_PARAM8	fun8;
			VAR_FUN_PARAM9	fun9;
		};

		//variable
		variable()
		{
		}

		variable(const variable& v)
		{
			*this = v;
		}

		variable(const variable* v)
		{
			*this = v;
		}

		variable(char i)
		{
			*this = (int)i;
		}

		variable(wchar_t i)
		{
			*this = (int)i;
		}

		variable(int i)
		{
			*this = i;
		}

		variable(float f)
		{
			*this = f;
		}

		variable(double d)
		{
			*this = d;
		}

		variable(const VAR_FUN_PARAM0 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM1 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM2 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM3 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM4 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM5 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM6 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM7 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM8 p)
		{
			*this = p;
		}

		variable(const VAR_FUN_PARAM9 p)
		{
			*this = p;
		}

		// =
		variable& operator = (const variable& v) //variable
		{
			ptr = v.ptr;
			return *this;
		}

		variable& operator = (const variable* v) //variable*
		{
			ptr = (variable*)v;
			return *this;
		}

		variable& operator = (char i) //char
		{
#ifdef _64BIT
			ptr = NULL;
#endif
			val = float((int)i);
			return *this;
		}

		variable& operator = (wchar_t i) //wchar_t
		{
#ifdef _64BIT
			ptr = NULL;
#endif
			val = float((int)i);
			return *this;
		}

		variable& operator = (int i) //int
		{
#ifdef _64BIT
			ptr = NULL;
#endif
			val = float(i);
			return *this;
		}

		variable& operator = (float f) //float
		{
#ifdef _64BIT
			ptr = NULL;
#endif
			val = f;
			return *this;
		}

		variable& operator = (double d) //double
		{
#ifdef _64BIT
			ptr = NULL;
#endif
			val = float(d);
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM0 p) //VAR_FUN_PARAM0
		{
			fun0 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM1 p) //VAR_FUN_PARAM1
		{
			fun1 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM2 p) //VAR_FUN_PARAM2
		{
			fun2 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM3 p) //VAR_FUN_PARAM3
		{
			fun3 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM4 p) //VAR_FUN_PARAM4
		{
			fun4 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM5 p) //VAR_FUN_PARAM5
		{
			fun5 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM6 p) //VAR_FUN_PARAM6
		{
			fun6 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM7 p) //VAR_FUN_PARAM7
		{
			fun7 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM8 p) //VAR_FUN_PARAM8
		{
			fun8 = p;
			return *this;
		}

		variable& operator = (const VAR_FUN_PARAM9 p) //VAR_FUN_PARAM8
		{
			fun9 = p;
			return *this;
		}

		// []
		variable& operator [] (char i)
		{
			return ptr[(int)i];
		}

		variable& operator [] (wchar_t i)
		{
			return ptr[(int)i];
		}

		variable& operator [] (int i)
		{
			return ptr[i];
		}

		variable& operator [] (float f)
		{
			return ptr[int(f)];
		}

		variable& operator [] (double d)
		{
			return ptr[int(d)];
		}

		// ()
		variable operator () ()
		{
			return fun0();
		}

		variable operator () (variable v0)
		{
			return fun1(v0);
		}

		variable operator () (variable v0, variable v1)
		{
			return fun2(v0, v1);
		}

		variable operator () (variable v0, variable v1, variable v2)
		{
			return fun3(v0, v1, v2);
		}

		variable operator () (variable v0, variable v1, variable v2, variable v3)
		{
			return fun4(v0, v1, v2, v3);
		}

		variable operator () (variable v0, variable v1, variable v2, variable v3, variable v4)
		{
			return fun5(v0, v1, v2, v3, v4);
		}

		variable operator () (variable v0, variable v1, variable v2, variable v3, variable v4, variable v5)
		{
			return fun6(v0, v1, v2, v3, v4, v5);
		}

		variable operator () (variable v0, variable v1, variable v2, variable v3, variable v4, variable v5, variable v6)
		{
			return fun7(v0, v1, v2, v3, v4, v5, v6);
		}

		variable operator () (variable v0, variable v1, variable v2, variable v3, variable v4, variable v5, variable v6, variable v7)
		{
			return fun8(v0, v1, v2, v3, v4, v5, v6, v7);
		}

		variable operator () (variable v0, variable v1, variable v2, variable v3, variable v4, variable v5, variable v6, variable v7, variable v8)
		{
			return fun9(v0, v1, v2, v3, v4, v5, v6, v7, v8);
		}

		// casting
		operator int () const
		{
			return int(val);
		}
	};

protected:
	static micpp* MICPP;
	static std::map<INT_T, std::string> CPPMAP;
	static std::map<std::string, INT_T> NAMEMAP;
	static bool ISNDEF;

	const char* name;

	std::map<std::string, variable*> varmap;	//c++ variable
	std::map<std::string, cppNode*> funmap;		//c++ function
	std::map<std::string, cppNode*> nodemap;	//cppGlobal, cppFunction

	std::list< std::pair<std::string, variable*> >* varstk;

	//
	//micpp
	micpp();

	//micpp
	~micpp();

	//<global>			-> ( "GLOBAL(" | "INDEX(" ) <name> ")" (("=" <expression>) | ("[<expression>]" ("={" <expression> ("," <expression>)* "}")?) | ("[]={" <expression> ("," <expression>)* "}"))? ";"
	cppNode* _global(CompilerInfo& info, bool reg);

	//<local>			-> ( "LOCAL(" ) <name> ")" (("=" <expression>) | ("[<expression>]" ("={" <expression> ("," <expression>)* "}")?) | ("[]={" <expression> ("," <expression>)* "}"))? ";"
	cppNode* _local(CompilerInfo& info);

	//<function>		-> "FUNCTION0(" <name> ")" (";" | <block>)
	//						| "FUNCTION1(" <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION2(" <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION3(" <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION4(" <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION5(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION6(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION7(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION8(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	//						| "FUNCTION9(" <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> "," <name> ")" (";" | <block>)
	cppNode* _function(CompilerInfo& info);

	//<if>				-> "if(" <expression> ")" <block> | <line> ("else if(" <expression> ")" <block> | <line>)* ("else" <block> | <line>)?
	cppNode* _if(CompilerInfo& info);

	//<for>				-> "for(" (<global> | <locla> | (<expression>)? ";") (<expression>) ";" <expression> ")" <block> | <line>
	cppNode* _for(CompilerInfo& info);

	//<block>			-> "{" (<block> | <global> | <local> | (("return")? <expression> ";") | <if> | <for> | "break" | "continue")* "}"
	cppNode* _block(CompilerInfo& info);

	//<line>			-> ("return")? <expression> ";") | <if> | <for> | break | continue
	cppNode* _line(CompilerInfo& info);

	//<expression>		-> <layer0> ("=" <layer0>)*
	cppNode* _expression(CompilerInfo& info);

	//<layer0>			-> <layer1> ("||" <layer1>)*
	cppNode* _layer0(CompilerInfo& info);

	//<layer1>			-> <layer2> ("&&" <layer2>)*
	cppNode* _layer1(CompilerInfo& info);

	//<layer2>			-> <layer3> (("==" | "!=") <layer3>)*
	cppNode* _layer2(CompilerInfo& info);

	//<layer3>			-> <layer4> (("<" | "<=" | ">" | ">=") <layer4>)*
	cppNode* _layer3(CompilerInfo& info);

	//<layer4>			-> <layer5> (("+" | "-") <layer5>)*
	cppNode* _layer4(CompilerInfo& info);

	//<layer5>			-> <layer6> (("*" | "/" | "%") <layer6>)*
	cppNode* _layer5(CompilerInfo& info);

	//<layer6>			-> ("!" | "+" | "-" | "&") <layer6>
	//					-> "(" <expression> ")"
	//					-> (number("." number "f")?) | ("0x"number)
	//					-> ("L") "'" ("\")? <char> "'"
	//					-> ((name) "::" )name?(( "(" (<expression> ("," <expression>)*) ")") | ("[" <expression> "]"))*
	cppNode* _layer6(CompilerInfo& info);

public:
//static variable
	static char STRING[MICPP_MAX_PATH]; //temp string
	static void (*PRINT)(const char*); //print function

//static function
	//Compiler
	//<start>			-> (<include>)* "namespace" <name> "{" (<global>)* (<function>)* "};"
	static micpp* Compiler(const char* filename, bool cpp=false);
	static micpp* Compiler(void* ptr, unsigned int size);

	//Create
	static micpp* Create(const char* name);

	//Destroy
	static micpp* Destroy(micpp* mi);

	//Find
	static micpp* Find(const char* name);

	//Name
	static const char* Name(micpp* mi);

	//Global
	static micpp* Global();

//non-static function
	//Variable
	micpp::variable* Variable(const char* name);

	//Function
	cppNode* Function(const char* name);

	//RegVar
	void RegVar(const char* name, variable* info=NULL);

	//RegFun
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM0 info=NULL);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM1 info, micpp::variable param0=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM2 info, micpp::variable param0=0, micpp::variable param1=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM3 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM4 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0, micpp::variable param3=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM5 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0, micpp::variable param3=0, micpp::variable param4=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM6 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0, micpp::variable param3=0, micpp::variable param4=0, micpp::variable param5=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM7 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0, micpp::variable param3=0, micpp::variable param4=0, micpp::variable param5=0, micpp::variable param6=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM8 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0, micpp::variable param3=0, micpp::variable param4=0, micpp::variable param5=0, micpp::variable param6=0, micpp::variable param7=0);
	void RegFun(const char* name, micpp::variable::VAR_FUN_PARAM9 info, micpp::variable param0=0, micpp::variable param1=0, micpp::variable param2=0, micpp::variable param3=0, micpp::variable param4=0, micpp::variable param5=0, micpp::variable param6=0, micpp::variable param7=0, micpp::variable param8=0);

//std
	INDEX(SIZEOF_VARIABLE) = sizeof(micpp::variable);
	INDEX(MAX_PARAM) = 9;

	//isdef
	FUNCTION0(isdef)
	{
		ISNDEF = false;
		return 1;
	}
	
	//cppfun
	static micpp::variable cppfun(micpp::variable fun);

	//mifun
	FUNCTION1(mifun, fun)
	{
		return fun;
	}

	//malloc
	static micpp::variable malloc(micpp::variable param);

	//free
	static micpp::variable free(micpp::variable param);

	//print_val
	FUNCTION2(print_val, param, c=0)
	{
		if(c == 0)
			sprintf(micpp::STRING, "%g", double(param.val));
		else
			sprintf(micpp::STRING, "%g%c", double(param.val), (char)int(c.val));

		PRINT(micpp::STRING);
		return param;
	}

	//print_var
	FUNCTION2(print_ptr, param, c=0)
	{
		if(c == 0)
			sprintf(micpp::STRING, "%p", param.ptr);
		else
			sprintf(micpp::STRING, "%p%c", param.ptr, (char)int(c.val));

		PRINT(micpp::STRING);
		return param;
	}

	//print_char
	FUNCTION2(print_char, param, c=0)
	{
		if(c == 0)
		{
			micpp::STRING[0] = (char)int(param.val);
			micpp::STRING[1] = '\0';
		}
		else
		{
			micpp::STRING[0] = (char)int(param.val);
			micpp::STRING[1] = (char)int(c.val);
			micpp::STRING[2] = '\0';

		}

		PRINT(micpp::STRING);
		return param;
	}

	//print_string
	FUNCTION2(print_string, param, c=0)
	{
		int i=0;
		for(;param[i] != 0; ++i)
			micpp::STRING[i] =(char)int(param[i].val);

		if(c != 0)
			micpp::STRING[i++] = (char)int(c.val);

		micpp::STRING[i] = '\0';

		PRINT(micpp::STRING);
		return param;
	}

	//copy
	FUNCTION3(copy, dest, soc, number)
	{
		for(int i=0; i < number; ++i)
			dest[i] = soc[i];

		return 1;
	}

	//offset
	FUNCTION2(offset, p, det)
	{
		return (micpp::variable*)((char*)p.ptr + det);
	}

	//ipart
	FUNCTION1(ipart, number)
	{
		return (int)number;
	}

	//fpart
	FUNCTION1(fpart, number)
	{
		return number.val - int(number.val);
	}
};

// +
inline micpp::variable operator + (micpp::variable n1, char n2)
{
	micpp::variable ret;
	ret = n1.val + float((int)n2);
	return ret;
}

inline micpp::variable operator + (micpp::variable n1, wchar_t n2)
{
	micpp::variable ret;
	ret = n1.val + float((int)n2);
	return ret;
}

inline micpp::variable operator + (micpp::variable n1, int n2)
{
	micpp::variable ret;
	ret.val = n1.val + float(n2);
	return ret;
}

inline micpp::variable operator + (micpp::variable n1, float n2)
{
	micpp::variable ret;
	ret.val = n1.val + float(n2);
	return ret;
}

inline micpp::variable operator + (micpp::variable n1, double n2)
{
	micpp::variable ret;
	ret.val = n1.val + float(n2);
	return ret;
}

inline micpp::variable operator + (char n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) + n2.val;
	return ret;
}

inline micpp::variable operator + (wchar_t n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) + n2.val;
	return ret;
}

inline micpp::variable operator + (int n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) + n2.val;
	return ret;
}

inline micpp::variable operator + (float n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) + n2.val;
	return ret;
}

inline micpp::variable operator + (double n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) + n2.val;
	return ret;
}

inline micpp::variable operator + (micpp::variable n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = n1.val + n2.val;
	return ret;
}

inline micpp::variable operator + (micpp::variable n)
{
	return n;
}

// +=
inline micpp::variable& operator += (micpp::variable& n1, char n2)
{
	n1.val += float((int)n2);
	return n1;
}

inline micpp::variable& operator += (micpp::variable& n1, wchar_t n2)
{
	n1.val += float((int)n2);
	return n1;
}

inline micpp::variable& operator += (micpp::variable& n1, int n2)
{
	n1.val += float(n2);
	return n1;
}

inline micpp::variable& operator += (micpp::variable& n1, float n2)
{
	n1.val += float(n2);
	return n1;
}

inline micpp::variable& operator += (micpp::variable& n1, double n2)
{
	n1.val += float(n2);
	return n1;
}

inline micpp::variable& operator += (micpp::variable& n1, micpp::variable n2)
{
	n1.val += n2.val;
	return n1;
}

// -
inline micpp::variable operator - (micpp::variable n1, char n2)
{
	micpp::variable ret;
	ret = n1.val - float((int)n2);
	return ret;
}

inline micpp::variable operator - (micpp::variable n1, wchar_t n2)
{
	micpp::variable ret;
	ret = n1.val - float((int)n2);
	return ret;
}

inline micpp::variable operator - (micpp::variable n1, int n2)
{
	micpp::variable ret;
	ret.val = n1.val - float(n2);
	return ret;
}

inline micpp::variable operator - (micpp::variable n1, float n2)
{
	micpp::variable ret;
	ret.val = n1.val - float(n2);
	return ret;
}

inline micpp::variable operator - (micpp::variable n1, double n2)
{
	micpp::variable ret;
	ret.val = n1.val - float(n2);
	return ret;
}

inline micpp::variable operator - (char n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) - n2.val;
	return ret;
}

inline micpp::variable operator - (wchar_t n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) - n2.val;
	return ret;
}

inline micpp::variable operator - (int n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) - n2.val;
	return ret;
}

inline micpp::variable operator - (float n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) - n2.val;
	return ret;
}

inline micpp::variable operator - (double n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) - n2.val;
	return ret;
}

inline micpp::variable operator - (micpp::variable n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = n1.val - n2.val;
	return ret;
}

inline micpp::variable operator - (micpp::variable n)
{
	micpp::variable ret;
	ret.val = -n.val;
	return ret;
}

// -=
inline micpp::variable& operator -= (micpp::variable& n1, char n2)
{
	n1.val -= float((int)n2);
	return n1;
}

inline micpp::variable& operator -= (micpp::variable& n1, wchar_t n2)
{
	n1.val -= float((int)n2);
	return n1;
}

inline micpp::variable& operator -= (micpp::variable& n1, int n2)
{
	n1.val -= float(n2);
	return n1;
}

inline micpp::variable& operator -= (micpp::variable& n1, float n2)
{
	n1.val -= float(n2);
	return n1;
}

inline micpp::variable& operator -= (micpp::variable& n1, double n2)
{
	n1.val -= float(n2);
	return n1;
}

inline micpp::variable& operator -= (micpp::variable& n1, micpp::variable n2)
{
	n1.val -= n2.val;
	return n1;
}

// *
inline micpp::variable operator * (micpp::variable n1, char n2)
{
	micpp::variable ret;
	ret = n1.val * float((int)n2);
	return ret;
}

inline micpp::variable operator * (micpp::variable n1, wchar_t n2)
{
	micpp::variable ret;
	ret = n1.val * float((int)n2);
	return ret;
}

inline micpp::variable operator * (micpp::variable n1, int n2)
{
	micpp::variable ret;
	ret.val = n1.val * float(n2);
	return ret;
}

inline micpp::variable operator * (micpp::variable n1, float n2)
{
	micpp::variable ret;
	ret.val = n1.val * float(n2);
	return ret;
}

inline micpp::variable operator * (micpp::variable n1, double n2)
{
	micpp::variable ret;
	ret.val = n1.val * float(n2);
	return ret;
}

inline micpp::variable operator * (char n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) * n2.val;
	return ret;
}

inline micpp::variable operator * (wchar_t n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) * n2.val;
	return ret;
}

inline micpp::variable operator * (int n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) * n2.val;
	return ret;
}

inline micpp::variable operator * (float n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) * n2.val;
	return ret;
}

inline micpp::variable operator * (double n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) * n2.val;
	return ret;
}

inline micpp::variable operator * (micpp::variable n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = n1.val * n2.val;
	return ret;
}

// *=
inline micpp::variable& operator *= (micpp::variable& n1, char n2)
{
	n1.val *= float((int)n2);
	return n1;
}

inline micpp::variable& operator *= (micpp::variable& n1, wchar_t n2)
{
	n1.val *= float((int)n2);
	return n1;
}

inline micpp::variable& operator *= (micpp::variable& n1, int n2)
{
	n1.val *= float(n2);
	return n1;
}

inline micpp::variable& operator *= (micpp::variable& n1, float n2)
{
	n1.val *= float(n2);
	return n1;
}

inline micpp::variable& operator *= (micpp::variable& n1, double n2)
{
	n1.val *= float(n2);
	return n1;
}

inline micpp::variable& operator *= (micpp::variable& n1, micpp::variable n2)
{
	n1.val *= n2.val;
	return n1;
}

// /
inline micpp::variable operator / (micpp::variable n1, char n2)
{
	micpp::variable ret;
	ret = n1.val / float((int)n2);
	return ret;
}

inline micpp::variable operator / (micpp::variable n1, wchar_t n2)
{
	micpp::variable ret;
	ret = n1.val / float((int)n2);
	return ret;
}

inline micpp::variable operator / (micpp::variable n1, int n2)
{
	micpp::variable ret;
	ret.val = n1.val / float(n2);
	return ret;
}

inline micpp::variable operator / (micpp::variable n1, float n2)
{
	micpp::variable ret;
	ret.val = n1.val / float(n2);
	return ret;
}

inline micpp::variable operator / (micpp::variable n1, double n2)
{
	micpp::variable ret;
	ret.val = n1.val / float(n2);
	return ret;
}

inline micpp::variable operator / (char n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) / n2.val;
	return ret;
}

inline micpp::variable operator / (wchar_t n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1) / n2.val;
	return ret;
}

inline micpp::variable operator / (int n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) / n2.val;
	return ret;
}

inline micpp::variable operator / (float n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) / n2.val;
	return ret;
}

inline micpp::variable operator / (double n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1) / n2.val;
	return ret;
}

inline micpp::variable operator / (micpp::variable n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = n1.val / n2.val;
	return ret;
}

// /=
inline micpp::variable& operator /= (micpp::variable& n1, char n2)
{
	n1.val /= float((int)n2);
	return n1;
}

inline micpp::variable& operator /= (micpp::variable& n1, wchar_t n2)
{
	n1.val /= float((int)n2);
	return n1;
}

inline micpp::variable& operator /= (micpp::variable& n1, int n2)
{
	n1.val /= float(n2);
	return n1;
}

inline micpp::variable& operator /= (micpp::variable& n1, float n2)
{
	n1.val /= float(n2);
	return n1;
}

inline micpp::variable& operator /= (micpp::variable& n1, double n2)
{
	n1.val /= float(n2);
	return n1;
}

inline micpp::variable& operator /= (micpp::variable& n1, micpp::variable n2)
{
	n1.val /= n2.val;
	return n1;
}

// %
inline micpp::variable operator % (micpp::variable n1, char n2)
{
	micpp::variable ret;
	ret = float(int(n1.val) % (int)n2);
	return ret;
}

inline micpp::variable operator % (micpp::variable n1, wchar_t n2)
{
	micpp::variable ret;
	ret = float(int(n1.val) % (int)n2);
	return ret;
}

inline micpp::variable operator % (micpp::variable n1, int n2)
{
	micpp::variable ret;
	ret.val = float(int(n1.val) % n2);
	return ret;
}

inline micpp::variable operator % (micpp::variable n1, float n2)
{
	micpp::variable ret;
	ret.val = float(int(n1.val) % (int)n2);
	return ret;
}

inline micpp::variable operator % (micpp::variable n1, double n2)
{
	micpp::variable ret;
	ret.val = float(int(n1.val) % (int)n2);
	return ret;
}

inline micpp::variable operator % (char n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1 % int(n2.val));
	return ret;
}

inline micpp::variable operator % (wchar_t n1, micpp::variable n2)
{
	micpp::variable ret;
	ret = float((int)n1 % int(n2.val));
	return ret;
}

inline micpp::variable operator % (int n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(n1 % int(n2.val));
	return ret;
}

inline micpp::variable operator % (float n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float((int)n1 % int(n2.val));
	return ret;
}

inline micpp::variable operator % (double n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float((int)n1 % int(n2.val));
	return ret;
}

inline micpp::variable operator % (micpp::variable n1, micpp::variable n2)
{
	micpp::variable ret;
	ret.val = float(int(n1.val) % int(n2.val));
	return ret;
}

// %=
inline micpp::variable& operator %= (micpp::variable& n1, char n2)
{
	n1.val = float(int(n1.val) % (int)n2);
	return n1;
}

inline micpp::variable& operator %= (micpp::variable& n1, wchar_t n2)
{
	n1.val = float(int(n1.val) % (int)n2);
	return n1;
}

inline micpp::variable& operator %= (micpp::variable& n1, int n2)
{
	n1.val = float(int(n1.val) % n2);
	return n1;
}

inline micpp::variable& operator %= (micpp::variable& n1, float n2)
{
	n1.val = float(int(n1.val) % (int)n2);
	return n1;
}

inline micpp::variable& operator %= (micpp::variable& n1, double n2)
{
	n1.val = float(int(n1.val) % (int)n2);
	return n1;
}

inline micpp::variable& operator %= (micpp::variable& n1, micpp::variable n2)
{
	n1.val = float(int(n1.val) % int(n2.val));
	return n1;
}

// ==
inline bool operator == (micpp::variable n1, char n2)
{
	return n1.val == float((int)n2);
}

inline bool operator == (micpp::variable n1, wchar_t n2)
{
	return n1.val == float((int)n2);
}

inline bool operator == (micpp::variable n1, int n2)
{
	return n1.val == float(n2);
}

inline bool operator == (micpp::variable n1, float n2)
{
	return n1.val == float(n2);
}

inline bool operator == (micpp::variable n1, double n2)
{
	return n1.val == float(n2);
}

inline bool operator == (char n1, micpp::variable n2)
{
	return float((int)n1) == n2.val;
}

inline bool operator == (wchar_t n1, micpp::variable n2)
{
	return float((int)n1) == n2.val;
}

inline bool operator == (int n1, micpp::variable n2)
{
	return n1 == int(n2.val);
}

inline bool operator == (float n1, micpp::variable n2)
{
	return float(n1) == n2.val;
}

inline bool operator == (double n1, micpp::variable n2)
{
	return float(n1) == n2.val;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM0 n2)
{
	return n1.fun0 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM1 n2)
{
	return n1.fun1 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM2 n2)
{
	return n1.fun2 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM3 n2)
{
	return n1.fun3 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM4 n2)
{
	return n1.fun4 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM5 n2)
{
	return n1.fun5 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM6 n2)
{
	return n1.fun6 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM7 n2)
{
	return n1.fun7 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM8 n2)
{
	return n1.fun8 == n2;
}

inline bool operator == (micpp::variable n1, micpp::variable::VAR_FUN_PARAM9 n2)
{
	return n1.fun9 == n2;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM0 n1, micpp::variable n2)
{
	return n1 == n2.fun0;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM1 n1, micpp::variable n2)
{
	return n1 == n2.fun1;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM2 n1, micpp::variable n2)
{
	return n1 == n2.fun2;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM3 n1, micpp::variable n2)
{
	return n1 == n2.fun3;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM4 n1, micpp::variable n2)
{
	return n1 == n2.fun4;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM5 n1, micpp::variable n2)
{
	return n1 == n2.fun5;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM6 n1, micpp::variable n2)
{
	return n1 == n2.fun6;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM7 n1, micpp::variable n2)
{
	return n1 == n2.fun7;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM8 n1, micpp::variable n2)
{
	return n1 == n2.fun8;
}

inline bool operator == (micpp::variable::VAR_FUN_PARAM9 n1, micpp::variable n2)
{
	return n1 == n2.fun9;
}

inline bool operator == (micpp::variable n1, micpp::variable n2)
{
	return n1.ptr == n2.ptr;
}

// !=
inline bool operator != (micpp::variable n1, char n2)
{
	return n1.val != float((int)n2);
}

inline bool operator != (micpp::variable n1, wchar_t n2)
{
	return n1.val != float((int)n2);
}

inline bool operator != (micpp::variable n1, int n2)
{
	return n1.val != float(n2);
}

inline bool operator != (micpp::variable n1, float n2)
{
	return n1.val != float(n2);
}

inline bool operator != (micpp::variable n1, double n2)
{
	return n1.val != float(n2);
}

inline bool operator != (char n1, micpp::variable n2)
{
	return float((int)n1) != n2.val;
}

inline bool operator != (wchar_t n1, micpp::variable n2)
{
	return float((int)n1) != n2.val;
}

inline bool operator != (int n1, micpp::variable n2)
{
	return n1 != int(n2.val);
}

inline bool operator != (float n1, micpp::variable n2)
{
	return float(n1) != n2.val;
}

inline bool operator != (double n1, micpp::variable n2)
{
	return float(n1) != n2.val;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM0 n2)
{
	return n1.fun0 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM1 n2)
{
	return n1.fun1 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM2 n2)
{
	return n1.fun2 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM3 n2)
{
	return n1.fun3 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM4 n2)
{
	return n1.fun4 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM5 n2)
{
	return n1.fun5 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM6 n2)
{
	return n1.fun6 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM7 n2)
{
	return n1.fun7 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM8 n2)
{
	return n1.fun8 != n2;
}

inline bool operator != (micpp::variable n1, micpp::variable::VAR_FUN_PARAM9 n2)
{
	return n1.fun9 != n2;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM0 n1, micpp::variable n2)
{
	return n1 != n2.fun0;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM1 n1, micpp::variable n2)
{
	return n1 != n2.fun1;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM2 n1, micpp::variable n2)
{
	return n1 != n2.fun2;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM3 n1, micpp::variable n2)
{
	return n1 != n2.fun3;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM4 n1, micpp::variable n2)
{
	return n1 != n2.fun4;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM5 n1, micpp::variable n2)
{
	return n1 != n2.fun5;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM6 n1, micpp::variable n2)
{
	return n1 != n2.fun6;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM7 n1, micpp::variable n2)
{
	return n1 != n2.fun7;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM8 n1, micpp::variable n2)
{
	return n1 != n2.fun8;
}

inline bool operator != (micpp::variable::VAR_FUN_PARAM9 n1, micpp::variable n2)
{
	return n1 != n2.fun9;
}

inline bool operator != (micpp::variable n1, micpp::variable n2)
{
	return n1.ptr != n2.ptr;
}

// >
inline bool operator > (micpp::variable n1, char n2)
{
	return n1.val > float((int)n2);
}

inline bool operator > (micpp::variable n1, wchar_t n2)
{
	return n1.val > float((int)n2);
}

inline bool operator > (micpp::variable n1, int n2)
{
	return n1.val > float(n2);
}

inline bool operator > (micpp::variable n1, float n2)
{
	return n1.val > float(n2);
}

inline bool operator > (micpp::variable n1, double n2)
{
	return n1.val > float(n2);
}

inline bool operator > (char n1, micpp::variable n2)
{
	return float((int)n1) > n2.val;
}

inline bool operator > (wchar_t n1, micpp::variable n2)
{
	return float((int)n1) > n2.val;
}

inline bool operator > (int n1, micpp::variable n2)
{
	return n1 > int(n2.val);
}

inline bool operator > (float n1, micpp::variable n2)
{
	return float(n1) > n2.val;
}

inline bool operator > (double n1, micpp::variable n2)
{
	return float(n1) > n2.val;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM0 n2)
{
	return n1.fun0 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM1 n2)
{
	return n1.fun1 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM2 n2)
{
	return n1.fun2 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM3 n2)
{
	return n1.fun3 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM4 n2)
{
	return n1.fun4 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM5 n2)
{
	return n1.fun5 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM6 n2)
{
	return n1.fun6 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM7 n2)
{
	return n1.fun7 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM8 n2)
{
	return n1.fun8 > n2;
}

inline bool operator > (micpp::variable n1, micpp::variable::VAR_FUN_PARAM9 n2)
{
	return n1.fun9 > n2;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM0 n1, micpp::variable n2)
{
	return n1 > n2.fun0;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM1 n1, micpp::variable n2)
{
	return n1 > n2.fun1;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM2 n1, micpp::variable n2)
{
	return n1 > n2.fun2;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM3 n1, micpp::variable n2)
{
	return n1 > n2.fun3;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM4 n1, micpp::variable n2)
{
	return n1 > n2.fun4;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM5 n1, micpp::variable n2)
{
	return n1 > n2.fun5;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM6 n1, micpp::variable n2)
{
	return n1 > n2.fun6;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM7 n1, micpp::variable n2)
{
	return n1 > n2.fun7;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM8 n1, micpp::variable n2)
{
	return n1 > n2.fun8;
}

inline bool operator > (micpp::variable::VAR_FUN_PARAM9 n1, micpp::variable n2)
{
	return n1 > n2.fun9;
}

inline bool operator > (micpp::variable n1, micpp::variable n2)
{
	return n1.val > n2.val;
}

// <
inline bool operator < (micpp::variable n1, char n2)
{
	return n1.val < float((int)n2);
}

inline bool operator < (micpp::variable n1, wchar_t n2)
{
	return n1.val < float((int)n2);
}

inline bool operator < (micpp::variable n1, int n2)
{
	return n1.val < float(n2);
}

inline bool operator < (micpp::variable n1, float n2)
{
	return n1.val < float(n2);
}

inline bool operator < (micpp::variable n1, double n2)
{
	return n1.val < float(n2);
}

inline bool operator < (char n1, micpp::variable n2)
{
	return float((int)n1) < n2.val;
}

inline bool operator < (wchar_t n1, micpp::variable n2)
{
	return float((int)n1) < n2.val;
}

inline bool operator < (int n1, micpp::variable n2)
{
	return n1 < int(n2.val);
}

inline bool operator < (float n1, micpp::variable n2)
{
	return float(n1) < n2.val;
}

inline bool operator < (double n1, micpp::variable n2)
{
	return float(n1) < n2.val;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM0 n2)
{
	return n1.fun0 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM1 n2)
{
	return n1.fun1 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM2 n2)
{
	return n1.fun2 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM3 n2)
{
	return n1.fun3 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM4 n2)
{
	return n1.fun4 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM5 n2)
{
	return n1.fun5 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM6 n2)
{
	return n1.fun6 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM7 n2)
{
	return n1.fun7 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM8 n2)
{
	return n1.fun8 < n2;
}

inline bool operator < (micpp::variable n1, micpp::variable::VAR_FUN_PARAM9 n2)
{
	return n1.fun9 < n2;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM0 n1, micpp::variable n2)
{
	return n1 < n2.fun0;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM1 n1, micpp::variable n2)
{
	return n1 < n2.fun1;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM2 n1, micpp::variable n2)
{
	return n1 < n2.fun2;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM3 n1, micpp::variable n2)
{
	return n1 < n2.fun3;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM4 n1, micpp::variable n2)
{
	return n1 < n2.fun4;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM5 n1, micpp::variable n2)
{
	return n1 < n2.fun5;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM6 n1, micpp::variable n2)
{
	return n1 < n2.fun6;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM7 n1, micpp::variable n2)
{
	return n1 < n2.fun7;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM8 n1, micpp::variable n2)
{
	return n1 < n2.fun8;
}

inline bool operator < (micpp::variable::VAR_FUN_PARAM9 n1, micpp::variable n2)
{
	return n1 < n2.fun9;
}

inline bool operator < (micpp::variable n1, micpp::variable n2)
{
	return n1.val < n2.val;
}

// >=
inline bool operator >= (micpp::variable n1, char n2)
{
	return n1.val >= float((int)n2);
}

inline bool operator >= (micpp::variable n1, wchar_t n2)
{
	return n1.val >= float((int)n2);
}

inline bool operator >= (micpp::variable n1, int n2)
{
	return n1.val >= float(n2);
}

inline bool operator >= (micpp::variable n1, float n2)
{
	return n1.val >= float(n2);
}

inline bool operator >= (micpp::variable n1, double n2)
{
	return n1.val >= float(n2);
}

inline bool operator >= (char n1, micpp::variable n2)
{
	return float((int)n1) >= n2.val;
}

inline bool operator >= (wchar_t n1, micpp::variable n2)
{
	return float((int)n1) >= n2.val;
}

inline bool operator >= (int n1, micpp::variable n2)
{
	return n1 >= int(n2.val);
}

inline bool operator >= (float n1, micpp::variable n2)
{
	return float(n1) >= n2.val;
}

inline bool operator >= (double n1, micpp::variable n2)
{
	return float(n1) >= n2.val;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM0 n2)
{
	return n1.fun0 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM1 n2)
{
	return n1.fun1 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM2 n2)
{
	return n1.fun2 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM3 n2)
{
	return n1.fun3 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM4 n2)
{
	return n1.fun4 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM5 n2)
{
	return n1.fun5 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM6 n2)
{
	return n1.fun6 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM7 n2)
{
	return n1.fun7 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM8 n2)
{
	return n1.fun8 >= n2;
}

inline bool operator >= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM9 n2)
{
	return n1.fun9 >= n2;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM0 n1, micpp::variable n2)
{
	return n1 >= n2.fun0;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM1 n1, micpp::variable n2)
{
	return n1 >= n2.fun1;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM2 n1, micpp::variable n2)
{
	return n1 >= n2.fun2;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM3 n1, micpp::variable n2)
{
	return n1 >= n2.fun3;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM4 n1, micpp::variable n2)
{
	return n1 >= n2.fun4;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM5 n1, micpp::variable n2)
{
	return n1 >= n2.fun5;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM6 n1, micpp::variable n2)
{
	return n1 >= n2.fun6;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM7 n1, micpp::variable n2)
{
	return n1 >= n2.fun7;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM8 n1, micpp::variable n2)
{
	return n1 >= n2.fun8;
}

inline bool operator >= (micpp::variable::VAR_FUN_PARAM9 n1, micpp::variable n2)
{
	return n1 >= n2.fun9;
}

inline bool operator >= (micpp::variable n1, micpp::variable n2)
{
	return n1.val >= n2.val;
}

// <=
inline bool operator <= (micpp::variable n1, char n2)
{
	return n1.val <= float((int)n2);
}

inline bool operator <= (micpp::variable n1, wchar_t n2)
{
	return n1.val <= float((int)n2);
}

inline bool operator <= (micpp::variable n1, int n2)
{
	return n1.val <= float(n2);
}

inline bool operator <= (micpp::variable n1, float n2)
{
	return n1.val <= float(n2);
}

inline bool operator <= (micpp::variable n1, double n2)
{
	return n1.val <= float(n2);
}

inline bool operator <= (char n1, micpp::variable n2)
{
	return float((int)n1) <= n2.val;
}

inline bool operator <= (wchar_t n1, micpp::variable n2)
{
	return float((int)n1) <= n2.val;
}

inline bool operator <= (int n1, micpp::variable n2)
{
	return n1 <= int(n2.val);
}

inline bool operator <= (float n1, micpp::variable n2)
{
	return float(n1) <= n2.val;
}

inline bool operator <= (double n1, micpp::variable n2)
{
	return float(n1) <= n2.val;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM0 n2)
{
	return n1.fun0 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM1 n2)
{
	return n1.fun1 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM2 n2)
{
	return n1.fun2 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM3 n2)
{
	return n1.fun3 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM4 n2)
{
	return n1.fun4 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM5 n2)
{
	return n1.fun5 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM6 n2)
{
	return n1.fun6 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM7 n2)
{
	return n1.fun7 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM8 n2)
{
	return n1.fun8 <= n2;
}

inline bool operator <= (micpp::variable n1, micpp::variable::VAR_FUN_PARAM9 n2)
{
	return n1.fun9 <= n2;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM0 n1, micpp::variable n2)
{
	return n1 <= n2.fun0;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM1 n1, micpp::variable n2)
{
	return n1 <= n2.fun1;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM2 n1, micpp::variable n2)
{
	return n1 <= n2.fun2;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM3 n1, micpp::variable n2)
{
	return n1 <= n2.fun3;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM4 n1, micpp::variable n2)
{
	return n1 <= n2.fun4;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM5 n1, micpp::variable n2)
{
	return n1 <= n2.fun5;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM6 n1, micpp::variable n2)
{
	return n1 <= n2.fun6;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM7 n1, micpp::variable n2)
{
	return n1 <= n2.fun7;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM8 n1, micpp::variable n2)
{
	return n1 <= n2.fun8;
}

inline bool operator <= (micpp::variable::VAR_FUN_PARAM9 n1, micpp::variable n2)
{
	return n1 <= n2.fun9;
}

inline bool operator <= (micpp::variable n1, micpp::variable n2)
{
	return n1.val <= n2.val;
}

//cppNode
#define MICPP_MAX_SYMBOL_LENGTH 4

class cppNode
{
public:
	//NODE_INTERFACE
	enum NODE_INTERFACE
	{
		NODE_NATIVE,
		NODE_VARIABLE,
		NODE_LOCAL,
		NODE_GLOBAL,
		NODE_OPERATOR,
		NODE_FLOW,
		NODE_RETURN,
		NODE_CONDITION,
		NODE_LOOP,
		NODE_BLOCK,
		NODE_FUNCTION,
		NODE_PARAM,

		NODE_UNKNOWN
	};

	//NODE_SYMBOL
	enum NODE_SYMBOL
	{
		//2 char
		SYMBOL_OR,
		SYMBOL_AND,
		SYMBOL_E,
		SYMBOL_NE,
		SYMBOL_LE,
		SYMBOL_GE,
		SYMBOL_SCOPE,

		//1 char
		SYMBOL_ASSIGNMENT,
		SYMBOL_ADDRESS,
		SYMBOL_NOT,
		SYMBOL_L,
		SYMBOL_G,

		SYMBOL_ADD,
		SYMBOL_SUB,
		SYMBOL_MUL,
		SYMBOL_DIV,
		SYMBOL_MOD,

		SYMBOL_ROUND_L,
		SYMBOL_ROUND_R,

		SYMBOL_SQARE_L,
		SYMBOL_SQARE_R,

		SYMBOL_CURLY_L,
		SYMBOL_CURLY_R,

		SYMBOL_COMMA,
		SYMBOL_SEMICOLON,
		SYMBOL_POINT,
		SYMBOL_QUOTES,
		SYMBOL_SLASH,

		SYMBOL_UNKNOWN
	};

	//NODE_NOUSE
	enum NODE_NOUSE
	{
		//2 char
		NOUSE_ADD_ADD,
		NOUSE_SUB_SUB,

		NOUSE_UNKNOWN
	};

	static char SYMBOL_STRING[SYMBOL_UNKNOWN][MICPP_MAX_SYMBOL_LENGTH];
	static char NOUSE_STRING[NOUSE_UNKNOWN][MICPP_MAX_SYMBOL_LENGTH];

	micpp* cpp;
	int line;

	//cppNode
	cppNode(micpp* _cpp, int _line)
	{
		cpp = _cpp;
		line = _line;
	}

	//~cppNode
	virtual ~cppNode()
	{
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		return 0;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_UNKNOWN;
	}

	// ()
	micpp::variable operator () ()
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[micpp::MAX_PARAM] = 0;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[micpp::MAX_PARAM] = 1;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[micpp::MAX_PARAM] = 2;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[micpp::MAX_PARAM] = 3;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2, micpp::variable v3)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[3] = v3;
		p[micpp::MAX_PARAM] = 4;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2, micpp::variable v3, micpp::variable v4)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[3] = v3;
		p[4] = v4;
		p[micpp::MAX_PARAM] = 5;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2, micpp::variable v3, micpp::variable v4, micpp::variable v5)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[3] = v3;
		p[4] = v4;
		p[5] = v5;
		p[micpp::MAX_PARAM] = 6;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2, micpp::variable v3, micpp::variable v4, micpp::variable v5, micpp::variable v6)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[3] = v3;
		p[4] = v4;
		p[5] = v5;
		p[6] = v6;
		p[micpp::MAX_PARAM] = 7;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2, micpp::variable v3, micpp::variable v4, micpp::variable v5, micpp::variable v6, micpp::variable v7)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[3] = v3;
		p[4] = v4;
		p[5] = v5;
		p[6] = v6;
		p[7] = v7;
		p[micpp::MAX_PARAM] = 8;

		return *Run(p).ptr;
	}

	micpp::variable operator () (micpp::variable v0, micpp::variable v1, micpp::variable v2, micpp::variable v3, micpp::variable v4, micpp::variable v5, micpp::variable v6, micpp::variable v7, micpp::variable v8)
	{
		micpp::variable p[micpp::MAX_PARAM + 1];
		p[0] = v0;
		p[1] = v1;
		p[2] = v2;
		p[3] = v3;
		p[4] = v4;
		p[5] = v5;
		p[6] = v6;
		p[7] = v7;
		p[8] = v8;
		p[micpp::MAX_PARAM] = 9;

		return *Run(p).ptr;
	}
};

#endif
