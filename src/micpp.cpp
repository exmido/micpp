//MiCpp project - micpp.cpp
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

#include "micpp.h"

#define MICPP_MAX_NAME 32

//cppNative
class cppNative : public cppNode //c++ function
{
public:
	int num;
	micpp::variable v;
	micpp::variable fun;
	micpp::variable node[micpp::MAX_PARAM];

	//cppNative
	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM0 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 0;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM1 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 1;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM2 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 2;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM3 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 3;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM4 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 4;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM5 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 5;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM6 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 6;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM7 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 7;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM8 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 8;
		fun = _fun;
	}

	cppNative(micpp* _cpp, int _line, micpp::variable::VAR_FUN_PARAM9 _fun)
		: cppNode(_cpp, _line)
	{
		v = 0;
		num = 9;
		fun = _fun;
	}

	cppNative(micpp::variable _fun)
		: cppNode(NULL, 0)
	{
		v = 0;
		num = -1;
		fun = _fun;
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		if(num >= 0)
		{
			while(param[micpp::MAX_PARAM] < num)
			{
				param[param[micpp::MAX_PARAM]] = node[param[micpp::MAX_PARAM]];
				param[micpp::MAX_PARAM] += 1;
			}
		}
		else
		{
			num = param[micpp::MAX_PARAM];
		}

		switch(num)
		{
		case 0:
			v = fun.fun0();
			break;

		case 1:
			v = fun.fun1(param[0]);
			break;

		case 2:
			v = fun.fun2(param[0], param[1]);
			break;

		case 3:
			v = fun.fun3(param[0], param[1], param[2]);
			break;

		case 4:
			v = fun.fun4(param[0], param[1], param[2], param[3]);
			break;

		case 5:
			v = fun.fun5(param[0], param[1], param[2], param[3], param[4]);
			break;

		case 6:
			v = fun.fun6(param[0], param[1], param[2], param[3], param[4], param[5]);
			break;

		case 7:
			v = fun.fun7(param[0], param[1], param[2], param[3], param[4], param[5], param[6]);
			break;

		case 8:
			v = fun.fun8(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7]);
			break;

		case 9:
			v = fun.fun9(param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7], param[8]);
			break;

		default:
			sprintf(micpp::STRING, "micpp %s(%d): function \"%p\" parameter number error...\n", cpp->name, line, fun.ptr);
			micpp::PRINT(micpp::STRING);
		}

		return &v;
	}

	//Type
	virtual NODE_INTERFACE Interface()
	{
		return NODE_NATIVE;
	}
};

//cppVariable
class cppVariable : public cppNode
{
public:
	micpp::variable	v;
	char			name[2][MICPP_MAX_NAME];

	//cppVariable
	cppVariable(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		v = 0;

		for(int i=0; i < 2; ++i)
			name[i][0] = '\0';
	}

	//~cppVariable
	virtual ~cppVariable()
	{
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		if(cpp && name[0][0] != '\0')
		{
			micpp* c = (name[1][0] != '\0') ? micpp::Find(name[1]) : cpp;
			if(c)
			{
				//find from local
				if(name[1][0] == '\0' && c == cpp && c->varstk)
				{
					for(std::list< std::pair<std::string, micpp::variable*> >::iterator vit = c->varstk->begin(); vit != c->varstk->end(); ++vit)
					{
						if(!strcmp(vit->first.c_str(), name[0]))
						{
							micpp::ISNDEF = true;
							return vit->second;
						}
					}
				}

				std::map<std::string, micpp::variable*>::iterator vit = c->varmap.find(name[0]);
				if(vit != c->varmap.end())
				{
#ifndef _DEBUG
					name[0][0] = '\0';
					strcpy(&name[1][0], "p");
#endif
					micpp::ISNDEF = true;
					v = vit->second;
					return v;
				}

				std::map<std::string, cppNode*>::iterator nit = c->nodemap.find(name[0]);
				if(nit != c->nodemap.end())
				{
#ifndef _DEBUG
					name[0][0] = '\0';
#endif
					v = (micpp::variable*)nit->second;

					//init global
					if(nit->second->Interface() == NODE_GLOBAL)
					{
#ifndef _DEBUG
						strcpy(&name[1][0], "p");
#endif
						micpp::ISNDEF = true;
						v = nit->second->Run().ptr;
						return v;
					}
#ifndef _DEBUG
					name[1][0] = '\0';
#endif
					micpp::ISNDEF = true;
					return &v;
				}

				nit = c->funmap.find(name[0]);
				if(nit != c->funmap.end())
				{
#ifndef _DEBUG
					name[0][0] = name[1][0] = '\0';
#endif
					v = (micpp::variable*)nit->second;
					micpp::ISNDEF = true;
					return &v;
				}

				//find from global
				if(name[1][0] == '\0')
				{
					c = micpp::Global();

					std::map<std::string, micpp::variable*>::iterator vit = c->varmap.find(name[0]);
					if(vit != c->varmap.end())
					{
#ifndef _DEBUG
						name[0][0] = '\0';
						strcpy(&name[1][0], "p");
#endif
						micpp::ISNDEF = true;
						v = vit->second;
						return v;
					}

					std::map<std::string, cppNode*>::iterator nit = c->nodemap.find(name[0]);
					if(nit != c->nodemap.end())
					{
#ifndef _DEBUG
						name[0][0] = '\0';
#endif
						v = (micpp::variable*)nit->second;

						//init global
						if(nit->second->Interface() == NODE_GLOBAL)
						{
#ifndef _DEBUG
							strcpy(&name[1][0], "p");
#endif
							micpp::ISNDEF = true;
							v = nit->second->Run().ptr;
							return v;
						}

#ifndef _DEBUG
						name[1][0] = '\0';
#endif
						micpp::ISNDEF = true;
						return &v;
					}

					nit = c->funmap.find(name[0]);
					if(nit != c->funmap.end())
					{
#ifndef _DEBUG
						name[0][0] = name[1][0] = '\0';
#endif
						v = (micpp::variable*)nit->second;
						micpp::ISNDEF = true;
						return &v;
					}
				}
			}

			//not find
			if(micpp::ISNDEF)
			{
				sprintf(micpp::STRING, "micpp %s(%d): can not find variable \"%s::%s\"\n", cpp->name, line, name[1][0] != '\0' ? name[1] : "", name[0]);
				micpp::PRINT(micpp::STRING);
			}

			micpp::ISNDEF = true;
			return &v;
		}
		else if(!strcmp(name[1], "p"))
		{
			micpp::ISNDEF = true;
			return v;
		}
		else if(!strcmp(name[1], "i")) //convert int to f32
		{
			v = (float)((int)(INT_T)v.ptr);
			name[1][0] = '\0';
		}

		micpp::ISNDEF = true;
		return &v;
	}

	//Type
	virtual NODE_INTERFACE Interface()
	{
		return NODE_VARIABLE;
	}
};

//cppLocal
class cppLocal : public cppVariable
{
public:
	cppNode* op;

	int size;
	int num;
	cppNode** node;

	//cppLocal
	cppLocal(micpp* _cpp, int _line)
		: cppVariable(_cpp, _line)
	{
		op = NULL;
		size = -1;
		num = 0;
		node = NULL;
	}

	//~cppLocal
	virtual ~cppLocal()
	{
		if(op)
			delete op;

		if(node)
		{
			for(int i=0; i < size; ++i)
			{
				if(node[i])
					delete node[i];
			}

			delete[] node;
		}
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		num = *op->Run().ptr;
		if((num ? num : 1) < size)
		{
			sprintf(micpp::STRING, "micpp %s(%d): variable \"%s::%s\" size error...\n",  cpp->name, line, name[1][0] != '\0' ? name[1] : "", name[0]);
			micpp::PRINT(micpp::STRING);
			return 0;
		}

		v = new micpp::variable[2];
		v[1] = num;

		if(num)
		{
			v[0] = new micpp::variable[num];

			for(int i=0; i < num; ++i)
			{
				if(i < size)
					v[0][i] = *node[i]->Run().ptr;
				else if(i > 0)
					v[0][i] = v.ptr[0].ptr[i-1];
			}
		}
		else
		{
			if(size > 0)
				v[0] = *node[0]->Run().ptr;
		}

		return v;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_LOCAL;
	}
};

//cppGlobal
class cppGlobal : public cppLocal
{
public:
	//cppGlobal
	cppGlobal(micpp* _cpp, int _line)
		: cppLocal(_cpp, line)
	{
		v.ptr = NULL;
	}

	//~cppGlobal
	virtual ~cppGlobal()
	{
		if(v.ptr)
		{
			if(v[1] > 0)
				delete[] v[0].ptr;

			delete[] v.ptr;
		}
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		if(v.ptr == NULL)
			cppLocal::Run();

		if(param != 0)
			return ((cppNode*)v.ptr->ptr)->Run(param).ptr;
		
		return v;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_GLOBAL;
	}
};

//cppOperator
class cppOperator : public cppNode
{
public:
	micpp::variable	v;

	NODE_SYMBOL		op;
	cppNode*		left;
	cppNode*		right;

	//cppOperator
	cppOperator(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		v = 0;
		op = SYMBOL_UNKNOWN;
		left = right = NULL;
	}

	//~cppOperator
	virtual ~cppOperator()
	{
		if(left)
			delete left;

		if(right)
			delete right;
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		micpp::variable vl, vr;

		switch(op)
		{
		case SYMBOL_ASSIGNMENT:
			vr = right->Run().ptr;
			vl = left->Run().ptr;
			v = *vl.ptr = *vr.ptr;
			return &v;

		case SYMBOL_ADDRESS:
			v = left->Run().ptr;
			return &v;

		case SYMBOL_OR:
			vl = *left->Run().ptr;
			if(vl != 0)
			{
				v = 1;
			}
			else
			{
				vr = *right->Run().ptr;
				v = (vr != 0 ? 1 : 0);
			}
			return &v;

		case SYMBOL_AND:
			vl = *left->Run().ptr;
			if(vl == 0)
			{
				v = 0;
			}
			else
			{
				vr = *right->Run().ptr;
				v = (vr != 0 ? 1 : 0);
			}
			return &v;

		case SYMBOL_E:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = ((vl == vr) ? 1 : 0);
			return &v;

		case SYMBOL_NE:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = ((vl != vr) ? 1 : 0);
			return &v;

		case SYMBOL_L:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = ((vl < vr) ? 1 : 0);
			return &v;

		case SYMBOL_LE:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = ((vl <= vr) ? 1 : 0);
			return &v;

		case SYMBOL_G:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = ((vl > vr) ? 1 : 0);
			return &v;

		case SYMBOL_GE:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = ((vl >= vr) ? 1 : 0);
			return &v;

		case SYMBOL_NOT:
			vl = *left->Run().ptr;
			v = (vl == 0 ? 1 : 0);
			return &v;

		case SYMBOL_ADD:
			vl = *left->Run().ptr;
			if(right)
			{
				vr = *right->Run().ptr;
				v = vl + vr;
			}
			else
			{
				v = vl;
			}
			return &v;

		case SYMBOL_SUB:
			vl = *left->Run().ptr;
			if(right)
			{
				vr = *right->Run().ptr;
				v = vl - vr;
			}
			else
			{
				v = -vl;
			}
			return &v;

		case SYMBOL_MUL:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = vl * vr;
			return &v;

		case SYMBOL_DIV:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = vl / vr;
			return &v;

		case SYMBOL_MOD:
			vl = *left->Run().ptr;
			vr = *right->Run().ptr;
			v = vl % vr;
			return &v;

		case SYMBOL_ROUND_L:
			vr.ptr = new micpp::variable[micpp::MAX_PARAM + 1];
			vl = *left->Run(right->Run(vr)).ptr;
			v = ((cppNode*)vl.ptr)->Run(vr);
			delete vr.ptr;
			return v;

		case SYMBOL_SQARE_L:
			vr = *right->Run().ptr;
			vl = *left->Run().ptr;
			return &vl.ptr[vr];

		default:
			break;
		}

		sprintf(micpp::STRING, "micpp %s(%d): unknown operator \"%d\"\n", cpp->name, line, op);
		micpp::PRINT(micpp::STRING);
		return 0;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_OPERATOR;
	}
};

//cppFlow
class cppFlow : public cppNode
{
public:
	enum
	{
		FLOW_NONE,
		FLOW_BREAK,
		FLOW_CONTINUE
	};

	micpp::variable v;

	//cppFlow
	cppFlow(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		v = 0;
	}

	//~cppFlow
	virtual ~cppFlow()
	{
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		return param[0] = v;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_RETURN;
	}
};

//cppReturn
class cppReturn : public cppNode
{
public:
	cppNode* op;
	micpp::variable v;

	//cppReturn
	cppReturn(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		op = NULL;
	}

	//~cppReturn
	virtual ~cppReturn()
	{
		delete op;
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		v = *op->Run().ptr;
		return &v;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_RETURN;
	}
};

//cppCondition
class cppCondition : public cppNode
{
public:
	cppNode* op;
	cppNode* block;
	cppNode* next;

	//cppCondition
	cppCondition(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		op = NULL;
		block = NULL;
		next = NULL;
	}

	//~cppCondition
	virtual ~cppCondition()
	{
		if(op)
			delete op;

		delete block;

		if(next)
			delete next;
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		for(cppCondition* p = this; p; p = (cppCondition*)p->next)
		{
			if(p->op == NULL || *p->op->Run().ptr)
				return p->block->Run(param);
		}

		return 0;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_CONDITION;
	}
};

//cppLoop
class cppLoop : public cppNode
{
public:
	cppNode* condition;
	cppNode* loop;
	cppNode* block;

	//cppLoop
	cppLoop(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		condition = NULL;
		loop = NULL;
		block = NULL;
	}

	//~cppLoop
	virtual ~cppLoop()
	{
		delete condition;
		delete loop;
		delete block;
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		micpp::variable p = cppFlow::FLOW_NONE;

		for(micpp::variable ret=0; *condition->Run().ptr; loop->Run())
		{
			ret = block->Run(&p);

			if(p == cppFlow::FLOW_BREAK)
				return 0;
			else if(p == cppFlow::FLOW_CONTINUE)
				ret = 0;
			else if(ret != 0)
				return ret;
		}

		return 0;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_LOOP;
	}
};

//cppBlock
class cppBlock : public cppNode
{
public:
	std::list<cppNode*> node;

	//cppBlock
	cppBlock(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
	}

	//~cppBlock
	virtual ~cppBlock()
	{
		for(std::list<cppNode*>::iterator it = node.begin(); it != node.end(); ++it)
			delete *it;
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		micpp::variable ret = 0;
		std::list<micpp::variable*> global;
		std::list<micpp::variable*> local;

		for(std::list<cppNode*>::iterator it = node.begin(); it != node.end() && ret.ptr == (micpp::variable*)NULL; ++it)
		{
			switch((*it)->Interface())
			{
			case NODE_GLOBAL:
				{
					micpp::variable* ptr = (*it)->Run().ptr;
					cpp->varstk->push_front(std::pair<std::string, micpp::variable*>(((cppGlobal*)(*it))->name[0], ptr));
					global.push_front(ptr);
				}
				break;
			case NODE_LOCAL:
				{
					micpp::variable* ptr = (*it)->Run().ptr;
					cpp->varstk->push_front(std::pair<std::string, micpp::variable*>(((cppLocal*)(*it))->name[0], ptr));
					local.push_front(ptr);
				}
				break;
			case NODE_OPERATOR:
				(*it)->Run();
				break;
			default:
				ret = (*it)->Run(param);
			}
		}

		for(std::list<micpp::variable*>::iterator it = global.begin(); it != global.end(); ++it)
		{
			for(std::list< std::pair<std::string, micpp::variable*> >::iterator sit = cpp->varstk->begin(); sit != cpp->varstk->end(); ++sit)
			{
				if(sit->second == *it)
				{
					cpp->varstk->erase(sit);
					break;
				}
			}
		}

		for(std::list<micpp::variable*>::iterator it = local.begin(); it != local.end(); ++it)
		{
			micpp::variable* v = *it;

			if(*it)
			{
				if((*it)[1] > 0)
					delete[] (*it)[0].ptr;
				
				delete[] *it;
			}

			for(std::list< std::pair<std::string, micpp::variable*> >::iterator sit = cpp->varstk->begin(); sit != cpp->varstk->end(); ++sit)
			{
				if(sit->second == *it)
				{
					cpp->varstk->erase(sit);
					break;
				}
			}
		}

		return ret;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_BLOCK;
	}
};

//cppFunction
class cppFunction : public cppNode
{
public:
	char name[micpp::MAX_PARAM + 1][MICPP_MAX_NAME]; //name[micpp::MAX_PARAM] as function name
	cppNode* node[micpp::MAX_PARAM + 1]; //node[micpp::MAX_PARAM] as block

	//cppFunction
	cppFunction(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		for(int i=0; i < micpp::MAX_PARAM + 1; ++i)
		{
			name[i][0] = '\0';
			node[i] = NULL;
		}
	}

	//~cppFunction
	virtual ~cppFunction()
	{
		for(int i=0; i < micpp::MAX_PARAM + 1; ++i)
		{
			if(node[i])
				delete node[i];
		}
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		std::list< std::pair<std::string, micpp::variable*> > stack;
		std::list< std::pair<std::string, micpp::variable*> >* varstk = cpp->varstk;

		cpp->varstk = &stack;
		std::list< std::pair<std::string, micpp::variable*> >::iterator it[micpp::MAX_PARAM] = {cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end(), cpp->varstk->end()};

		for(int i=0; i < micpp::MAX_PARAM; ++i)
		{
			if(name[i][0] != '\0')
			{
				if(param[micpp::MAX_PARAM] <= i)
				{
					if(node[i])
					{
						param[i] = *node[i]->Run(param).ptr;
						param[micpp::MAX_PARAM] += 1;
					}
					else
					{
						sprintf(micpp::STRING, "micpp %s(%d): function \"%s()\" param error\n", cpp->name, line, name[micpp::MAX_PARAM]);
						micpp::PRINT(micpp::STRING);
						cpp->varstk = varstk;
						return 0;
					}
				}

				cpp->varstk->push_front(std::pair<std::string, micpp::variable*>(name[i], &param[i]));
				it[i] = cpp->varstk->begin();
			}
			else
			{
				if(param[micpp::MAX_PARAM] != i)
				{
					sprintf(micpp::STRING, "micpp %s(%d): function \"%s()\" param error\n", cpp->name, line, name[micpp::MAX_PARAM]);
					micpp::PRINT(micpp::STRING);
					cpp->varstk = varstk;
					return 0;
				}

				break;
			}
		}

		micpp::variable ret = node[micpp::MAX_PARAM]->Run(param);

		for(int i=0; i < micpp::MAX_PARAM; ++i)
		{
			if(it[i] != cpp->varstk->end())
				cpp->varstk->erase(it[i]);
		}

		cpp->varstk = varstk;
		return ret;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_FUNCTION;
	}
};

//cppParam
class cppParam : public cppNode
{
public:
	int num;
	cppNode* node[micpp::MAX_PARAM];

	//cppParam
	cppParam(micpp* _cpp, int _line)
		: cppNode(_cpp, _line)
	{
		num = 0;

		for(int i=0; i < micpp::MAX_PARAM; ++i)
			node[i] = NULL;
	}

	//~cppParam
	virtual ~cppParam()
	{
		for(int i=0; i < micpp::MAX_PARAM; ++i)
		{
			if(node[i])
				delete node[i];
		}
	}

	//Run
	virtual micpp::variable Run(micpp::variable param=0)
	{
		for(int i=0; i < num; ++i)
			param[i] = *node[i]->Run(param).ptr;

		param[micpp::MAX_PARAM] = num;
		return param;
	}

	//Interface
	virtual NODE_INTERFACE Interface()
	{
		return NODE_PARAM;
	}
};

//cppNode
char cppNode::SYMBOL_STRING[cppNode::SYMBOL_UNKNOWN][MICPP_MAX_SYMBOL_LENGTH] =
{
	//2 char
	"||",
	"&&",
	"==",
	"!=",
	"<=",
	">=",
	"::",

	//1 char
	"=",
	"&",
	"!",
	"<",
	">",
	"+",
	"-",
	"*",
	"/",
	"%",
	"(",
	")",
	"[",
	"]",
	"{",
	"}",
	",",
	";",
	".",
	"\'",
	"\\"
};

char cppNode::NOUSE_STRING[NOUSE_UNKNOWN][MICPP_MAX_SYMBOL_LENGTH] =
{
	//2 char
	"++",
	"--"
};

//CompilerInfo
class CompilerInfo
{
public:
	char*	ptr;
	char*	end;

	char	token[32];
	int		line;

	bool	error;
	FILE*	fp;

	//CompilerInfo
	CompilerInfo(void* _ptr, int _size)
	{
		ptr = (char*)_ptr;
		end = ptr + _size;
		token[0] = '\0';
		line = 1;
		error = false;
		fp = NULL;
	}
};

//micpp
//TOKEN_TYPE
enum TOKEN_TYPE
{
	TYPE_NUMBER,
	TYPE_STRING,
	TYPE_SYMBOL,
	TYPE_UNKNOWN
};

//Token
bool Token(CompilerInfo& info, TOKEN_TYPE type, const char* str=NULL)
{
	info.token[0] = '\0';
	int size = info.end - info.ptr;

	//null char and comment
	for(int comment = 0; size; size = info.end - info.ptr)
	{
		if(size >= 2 && comment == 0 && info.ptr[0] == '/' && info.ptr[1] == '/') // //
		{
			comment = 1;
			++info.ptr;
		}
		else if(size >= 2 && comment == 0 && info.ptr[0] == '/' && info.ptr[1] == '*') // /*
		{
			comment = 2;
			++info.ptr;
		}
		else if(size >= 2 && comment == 2 && info.ptr[0] == '*' && info.ptr[1] == '/') // */
		{
			comment = 0;
			++info.ptr;
		}
		else if(comment == 0 && info.ptr[0] == '#') // #
		{
			comment = 1;
		}
		else if(*info.ptr == '\n')
		{
			if(comment == 1)
				comment = 0;

			++info.line;
		}
		else if(*info.ptr == '\0')
		{
			return false;
		}
		else if(comment == 0 && (type == TYPE_UNKNOWN || *info.ptr != ' ') && (*info.ptr < 7 || *info.ptr > 13))
		{
			/*
			7	\a	alert (beep)
			8	\b	backspace
			9	\t	tab
			10	\n	newline
			11	\v	vertical tab
			12	\f	form feed (page feed)
			13	\r	carriage return
			*/
			break;
		}

		++info.ptr;
	}

	if(size < 0)
		return false;

	char* p = info.ptr;
	switch(type)
	{
	case TYPE_NUMBER:
		if(*p >= '0' && *p <= '9') //number
		{
			do
			{
				++p;
			}
			while(p < info.end && *p >= '0' && *p <= '9');

			goto _LABEL_TOKEN_TRUE;
		}
		return false;
	case TYPE_STRING:
		if(*p == '_' || (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) //string
		{
			do
			{
				++p;
			}
			while(p < info.end && (*p == '_' || (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9')));

			goto _LABEL_TOKEN_TRUE;
		}
		return false;
	case TYPE_SYMBOL:
		for(int i=0; i < cppNode::NOUSE_UNKNOWN; ++i)
		{
			int len = (int)strlen(cppNode::NOUSE_STRING[i]);
			if(size >= len && !strncmp(p, cppNode::NOUSE_STRING[i], len)) //no use
				return false;
		}

		for(int i=0; i < cppNode::SYMBOL_UNKNOWN; ++i)
		{
			int len = (int)strlen(cppNode::SYMBOL_STRING[i]);
			if(size >= len && !strncmp(p, cppNode::SYMBOL_STRING[i], len)) //symbol
			{
				for(; len > 0; --len)
					++p;

				goto _LABEL_TOKEN_TRUE;
			}
		}
		return false;
	default:
		++p;
	}

_LABEL_TOKEN_TRUE:
	size = p - info.ptr;
	if(size < MICPP_MAX_NAME)
	{
		strncpy(info.token, info.ptr, size);
		info.token[size] = '\0';
	}
	else
	{
		return false;
	}

	if(str && strcmp(info.token, str))
		return false;

	info.ptr = p;
	return true;
}

//OptimizeExpression
cppNode* OptimizeExpression(cppOperator* node, micpp* cpp, int line)
{
	cppVariable* left = NULL;
	cppVariable* right = NULL;

	//check variable
	if(node->left)
	{
		if(node->left->Interface() == cppNode::NODE_VARIABLE && ((cppVariable*)node->left)->name[0][0] == '\0')
			left = (cppVariable*)node->left;
		else
			return node;
	}

	if(node->right)
	{
		if(node->right->Interface() == cppNode::NODE_VARIABLE && ((cppVariable*)node->right)->name[0][0] == '\0')
			right = (cppVariable*)node->right;
		else
			return node;
	}

	//
	cppVariable* ret = new cppVariable(cpp, line);

	//check float
	if((left && left->name[1][0] == '\0') || (right && right->name[1][0] == '\0'))
	{
		ret->v = *node->Run().ptr;
		delete node;
		return ret;
	}

	INT_T l = left ? (INT_T)left->v.ptr : 0;
	INT_T r = right ? (INT_T)right->v.ptr : 0;

	strcpy(ret->name[1], "i");

	switch(node->op)
	{
	case cppNode::SYMBOL_ADD:
		if(right)
			ret->v.ptr = (micpp::variable*)(l + r);
		else
			ret->v.ptr = (micpp::variable*)(l);
		break;

	case cppNode::SYMBOL_SUB:
		if(right)
			ret->v.ptr = (micpp::variable*)(l - r);
		else
			ret->v.ptr = (micpp::variable*)(-l);
		break;

	case cppNode::SYMBOL_MUL:
		ret->v.ptr = (micpp::variable*)(l * r);
		break;

	case cppNode::SYMBOL_DIV:
		ret->v.ptr = (micpp::variable*)(l / r);
		break;

	case cppNode::SYMBOL_MOD:
		ret->v.ptr = (micpp::variable*)(l % r);
		break;

	default:
		break;
	}

	delete node;
	return ret;
}

//print
void print(const char* str)
{
	printf("%s", str);
}

micpp* micpp::MICPP = NULL;
std::map<INT_T, std::string> micpp::CPPMAP;
std::map<std::string, INT_T> micpp::NAMEMAP;
bool micpp::ISNDEF = true;

char micpp::STRING[MICPP_MAX_PATH];
void (*micpp::PRINT)(const char*) = print;

//micpp
micpp::micpp()
{
	name = NULL;
	varstk = NULL;
}

//micpp
micpp::~micpp()
{
	for(std::map<std::string, cppNode*>::iterator it = nodemap.begin(); it != nodemap.end(); ++it)
		delete it->second;

	for(std::map<std::string, cppNode*>::iterator it = funmap.begin(); it != funmap.end(); ++it)
		delete it->second;
}

//Compiler
//<start>			-> (<include>)* "namespace" <name> "{" (<global>)* (<function>)* "};"
micpp* micpp::Compiler(const char* filename, bool cpp)
{
	//load file
	unsigned char* ptr;
	unsigned int size;

	FILE *fp = fopen(filename, "rb");
	if(fp == NULL)
		return NULL;

	//get file length.
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	ptr = new unsigned char[size];

	fseek(fp, 0, SEEK_SET);
	fread(ptr, size, 1, fp);

	fclose(fp);

	//
	micpp* ret = NULL;

	CompilerInfo info(ptr, size);

	if(cpp)
	{
		strcpy(micpp::STRING, filename);
		strcpy(strrchr(micpp::STRING, '.'), ".cpp");

		info.fp = fopen(micpp::STRING, "wb");
	}

	if(Token(info, TYPE_STRING, "namespace") == false || Token(info, TYPE_STRING) == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", filename, info.line, "miss namespace");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	ret = Create(info.token);
	if(ret == NULL)
	{
		delete[] ptr;
		return NULL;
	}

	if(cpp)
	{
		char* c = strrchr((char*)filename, '\\');
		c = (c ? c + 1 : (char*)filename);

		fprintf(info.fp, "#include \"%s\"\r\n", c);
		fprintf(info.fp, "\r\n");
		fprintf(info.fp, "//%s\r\n", info.token);
		fprintf(info.fp, "namespace %s\r\n", info.token);
		fprintf(info.fp, "{\r\n");
		fprintf(info.fp, "\t//_RegCpp\r\n");
		fprintf(info.fp, "\tvoid _RegCpp(micpp* _cpp)\r\n");
		fprintf(info.fp, "\t{\r\n");
	}

	if(Token(info, TYPE_SYMBOL, "{") == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", ret->name, info.line, "miss {");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	while(!info.error)
	{
		if(ret->_global(info, true))
			continue;

		if(ret->_function(info))
			continue;

		break;
	}

	if(info.error)
		goto _COMPILER_ERROR;

	if(Token(info, TYPE_SYMBOL, "}") == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", ret->name, info.line, "miss }");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	if(Token(info, TYPE_SYMBOL, ";") == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", ret->name, info.line, "miss ;");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	if(cpp)
	{
		fprintf(info.fp, "\t}\r\n");
		fprintf(info.fp, "};\r\n");

		fclose(info.fp);
	}

	delete[] ptr;
	return ret;

_COMPILER_ERROR:
	info.error = true;
	if(ret)
		Destroy(ret);

	delete[] ptr;
	return NULL;
}

micpp* micpp::Compiler(void* ptr, unsigned int size)
{
	micpp* ret = NULL;

	CompilerInfo info(ptr, size);

	if(Token(info, TYPE_STRING, "namespace") == false || Token(info, TYPE_STRING) == false)
	{
		sprintf(micpp::STRING, "micpp (%d) : %s\n", info.line, "miss namespace");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	ret = Create(info.token);
	if(ret == NULL)
	{
		delete[] ptr;
		return NULL;
	}

	if(Token(info, TYPE_SYMBOL, "{") == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", ret->name, info.line, "miss {");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	while(!info.error)
	{
		if(ret->_global(info, true))
			continue;

		if(ret->_function(info))
			continue;

		break;
	}

	if(info.error)
		goto _COMPILER_ERROR;

	if(Token(info, TYPE_SYMBOL, "}") == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", ret->name, info.line, "miss }");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	if(Token(info, TYPE_SYMBOL, ";") == false)
	{
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", ret->name, info.line, "miss ;");
		micpp::PRINT(micpp::STRING);
		goto _COMPILER_ERROR;
	}

	return ret;

_COMPILER_ERROR:
	info.error = true;
	if(ret)
		Destroy(ret);

	return NULL;
}

//Create
micpp* micpp::Create(const char* name)
{
	micpp* ret = NULL;
	if(NAMEMAP.find(name) != NAMEMAP.end())
		return NULL;

	Global();

	ret = new micpp;
	CPPMAP.insert(std::pair<INT_T, std::string>((INT_T)ret, name));
	NAMEMAP.insert(std::pair<std::string, INT_T>(name, (INT_T)ret));
	return ret;
}

//Destroy
micpp* micpp::Destroy(micpp* mi)
{
	if(mi)
	{
		NAMEMAP.erase(CPPMAP.find((INT_T)mi)->second);
		CPPMAP.erase((INT_T)mi);
		delete mi;
	}

	if(CPPMAP.empty() && MICPP)
	{
		delete MICPP;
		MICPP = NULL;
	}

	return NULL;
}

//Find
micpp* micpp::Find(const char* name)
{
	if(!strcmp(name, "micpp"))
		return Global();

	std::map<std::string, INT_T>::iterator it = NAMEMAP.find(name);
	return it != NAMEMAP.end() ? (micpp*)it->second : NULL;
}

//Name
const char* micpp::Name(micpp* mi)
{
	static char ret[] = "micpp";
	if(mi == Global())
		return ret;

	std::map<INT_T, std::string>::iterator it = CPPMAP.find((INT_T)mi);
	return it != CPPMAP.end() ? it->second.c_str() : NULL;
}

//Global
micpp* micpp::Global()
{
	if(MICPP == NULL)
	{
		MICPP = new micpp;

		//var
		static micpp::variable MICPP_IS_CPP = 0;
		MICPP->RegVar("ISCPP", &MICPP_IS_CPP);

		static micpp::variable MICPP_SIZEOF_VARIABLE = micpp::SIZEOF_VARIABLE;
		MICPP->RegVar("SIZEOF_VARIABLE", &MICPP_SIZEOF_VARIABLE);

		static micpp::variable MICPP_MAX_PARAM = micpp::MAX_PARAM;
		MICPP->RegVar("MAX_PARAM", &MICPP_MAX_PARAM);

		static micpp::variable MICPP_F32_MAX = FLT_MAX;
		MICPP->RegVar("F32_MAX", &MICPP_F32_MAX);

		static micpp::variable MICPP_F32_MIN = FLT_MIN;
		MICPP->RegVar("F32_MIN", &MICPP_F32_MIN);

		static micpp::variable MICPP_INT_MAX = (micpp::variable*)INT_MAX;
		MICPP->RegVar("INT_MAX", &MICPP_INT_MAX);

		static micpp::variable MICPP_INT_MIN = (micpp::variable*)INT_MIN;
		MICPP->RegVar("INT_MIN", &MICPP_INT_MIN);

		//fun
		MICPP->RegFun("ISDEF", micpp::isdef);
		MICPP->RegFun("CPPFUN", micpp::cppfun);
		MICPP->RegFun("MIFUN", micpp::mifun);

		MICPP->RegFun("malloc", micpp::malloc);
		MICPP->RegFun("free", micpp::free);

		MICPP->RegFun("print_val", micpp::print_val);
		MICPP->RegFun("print_ptr", micpp::print_ptr);
		MICPP->RegFun("print_char", micpp::print_char);
		MICPP->RegFun("print_string", micpp::print_string);

		MICPP->RegFun("copy", micpp::copy);
		MICPP->RegFun("offset", micpp::offset);
		MICPP->RegFun("ipart", micpp::ipart);
		MICPP->RegFun("fpart", micpp::fpart);
	}

	return MICPP;
}

//Variable
micpp::variable* micpp::Variable(const char* name)
{
	if(name && name[0] != '\0')
	{
		std::map<std::string, cppNode*>::iterator nit = nodemap.find((char*)name);
		if(nit != nodemap.end())
			return nit->second->Run().ptr;

		std::map<std::string, variable*>::iterator vit = varmap.find((char*)name);
		if(vit != varmap.end())
			return vit->second;
	}

	return NULL;
}

//Function
cppNode* micpp::Function(const char* name)
{
	if(name && name[0] != '\0')
	{
		std::map<std::string, cppNode*>::iterator it = nodemap.find((char*)name);
		if(it != nodemap.end())
			return it->second;

		it = funmap.find((char*)name);
		if(it != funmap.end())
			return it->second;
	}

	return NULL;
}

//RegVar
void micpp::RegVar(const char* name, variable* info)
{
	std::map<std::string, variable*>::iterator it = varmap.find((char*)name);
	if(it != varmap.end())
		varmap.erase(it);

	if(info)
		varmap.insert(std::pair<std::string, variable*>(name, info));
}

//RegFun
void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM0 info)
{
	std::map<std::string, cppNode*>::iterator it = funmap.find((char*)name);
	if(it != funmap.end())
	{
		delete it->second;
		funmap.erase(it);
	}

	if(info)
	{
		cppNode* node = new cppNative(this, 0, info);
		funmap.insert(std::pair<std::string, cppNode*>(name, node));
	}
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM1 info, micpp::variable param0)
{
	cppNative* node = new cppNative(this, -1, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM2 info, micpp::variable param0, micpp::variable param1)
{
	cppNative* node = new cppNative(this, -2, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM3 info, micpp::variable param0, micpp::variable param1, micpp::variable param2)
{
	cppNative* node = new cppNative(this, -3, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM4 info, micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3)
{
	cppNative* node = new cppNative(this, -4, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
	node->node[3] = param3;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM5 info, micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4)
{
	cppNative* node = new cppNative(this, -5, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
	node->node[3] = param3;
	node->node[4] = param4;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM6 info, micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5)
{
	cppNative* node = new cppNative(this, -6, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
	node->node[3] = param3;
	node->node[4] = param4;
	node->node[5] = param5;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM7 info, micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5, micpp::variable param6)
{
	cppNative* node = new cppNative(this, -7, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
	node->node[3] = param3;
	node->node[4] = param4;
	node->node[5] = param5;
	node->node[6] = param6;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM8 info, micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5, micpp::variable param6, micpp::variable param7)
{
	cppNative* node = new cppNative(this, -8, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
	node->node[3] = param3;
	node->node[4] = param4;
	node->node[5] = param5;
	node->node[6] = param6;
	node->node[7] = param7;
}

void micpp::RegFun(const char* name, micpp::variable::VAR_FUN_PARAM9 info, micpp::variable param0, micpp::variable param1, micpp::variable param2, micpp::variable param3, micpp::variable param4, micpp::variable param5, micpp::variable param6, micpp::variable param7, micpp::variable param8)
{
	cppNative* node = new cppNative(this, -9, info);
	funmap.insert(std::pair<std::string, cppNode*>(name, node));

	node->node[0] = param0;
	node->node[1] = param1;
	node->node[2] = param2;
	node->node[3] = param3;
	node->node[4] = param4;
	node->node[5] = param5;
	node->node[6] = param6;
	node->node[7] = param7;
	node->node[8] = param8;
}

//cppfun
micpp::variable micpp::cppfun(micpp::variable fun)
{
	static cppNative* NODE = NULL;
	if(NODE)
	{
		delete NODE;
		NODE = NULL;
	}
	
	if(fun != 0)
		NODE = new cppNative(fun);

	return (micpp::variable*)NODE;
}

//malloc
micpp::variable micpp::malloc(micpp::variable param)
{
	return new variable[param];
}

//free
micpp::variable micpp::free(micpp::variable param)
{
	delete[] param.ptr;
	return 0;
}

//<global>			-> ( "GLOBAL(" | "INDEX(" ) <name> ")" (("=" <expression>) | ("[<expression>]" ("={" <expression> ("," <expression>)* "}")?) | ("[]={" <expression> ("," <expression>)* "}"))? ";"
cppNode* micpp::_global(CompilerInfo& info, bool reg)
{
	if(info.error)
		return NULL;

	cppGlobal* ret = new cppGlobal(this, info.line);

	if((Token(info, TYPE_STRING, "GLOBAL") || Token(info, TYPE_STRING, "INDEX")) && strcpy(ret->name[1], info.token) && Token(info, TYPE_SYMBOL, "("))
	{
		if(Token(info, TYPE_STRING) == false)
			goto _GLOBAL_ERROR;

		strcpy(ret->name[0], info.token);
		if(Token(info, TYPE_SYMBOL, ")") == false)
			goto _GLOBAL_ERROR;

		if(Token(info, TYPE_SYMBOL, "="))
		{
			ret->op = new cppVariable(this, info.line);
			((cppVariable*)ret->op)->v = 0;

			ret->size = 1;
			ret->node = new cppNode*[1];

			ret->node[0] = _expression(info);
			if(ret->node[0] == NULL)
				goto _GLOBAL_ERROR;
		}
		else if(Token(info, TYPE_SYMBOL, "["))
		{
			if(Token(info, TYPE_SYMBOL, "]") == false)
			{
				ret->op = _expression(info);
				if(Token(info, TYPE_SYMBOL, "]") == false)
					goto _GLOBAL_ERROR;
			}

			if(Token(info, TYPE_SYMBOL, "="))
			{
				if(Token(info, TYPE_SYMBOL, "{") == false)
					goto _GLOBAL_ERROR;

				std::list<cppNode*> nodelist;
				for(ret->size = 0;;)
				{
					cppNode* node = _expression(info);

					if(node == NULL || info.error)
					{
						for(std::list<cppNode*>::iterator it = nodelist.begin(); it != nodelist.end(); ++it)
							delete *it;

						goto _GLOBAL_ERROR;
					}
					else
					{
						nodelist.push_back(node);
						++ret->size;
					}

					if(Token(info, TYPE_SYMBOL, ",") == false)
						break;
				}

				if(ret->size <= 0)
					goto _GLOBAL_ERROR;

				ret->node = new cppNode*[ret->size];
				std::list<cppNode*>::iterator it = nodelist.begin();
				for(int i=0; i < ret->size; ++i)
				{
					ret->node[i] = *it;
					++it;
				}

				if(info.error || Token(info, TYPE_SYMBOL, "}") == false)
					goto _GLOBAL_ERROR;
			}

			if(ret->op == NULL)
			{
				if(ret->size > 0)
				{
					ret->op = new cppVariable(this, info.line);
					((cppVariable*)ret->op)->v = ret->size;
				}
				else
				{
					goto _GLOBAL_ERROR;
				}
			}
		}
		else
		{
			ret->op = new cppVariable(this, info.line);
			((cppVariable*)ret->op)->v = 0;
		}

		if(Token(info, TYPE_SYMBOL, ";"))
		{
			if(reg)
			{
				if(nodemap.find(ret->name[0]) != nodemap.end())
				{
					info.error = true;
					sprintf(micpp::STRING, "micpp %s(%d) : \"%s\" redefine\n", micpp::Name(this), info.line, ret->name[0]);
					micpp::PRINT(micpp::STRING);
					delete ret;
					return NULL;
				}

				nodemap.insert(std::pair<std::string, cppNode*>(ret->name[0], ret));
			}

			if(info.fp && reg)
			{
				if(!strcmp(ret->name[1], "GLOBAL"))
				{
					fprintf(info.fp, "\t\t_cpp->RegVar(\"%s\", &%s);\r\n", ret->name[0], ret->name[0]);
				}
				else if(!strcmp(ret->name[1], "INDEX"))
				{
					fprintf(info.fp, "\t\tstatic micpp::variable %s_%s = %s;\r\n", name, ret->name[0], ret->name[0]);
					fprintf(info.fp, "\t\t_cpp->RegVar(\"%s\", &%s_%s);\r\n", ret->name[0], name, ret->name[0]);
				}
			}

			return ret;
		}

_GLOBAL_ERROR:
		info.error = true;
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "global format error");
		micpp::PRINT(micpp::STRING);
		delete ret;
	}

	delete ret;
	return NULL;
}

//<local>			-> ( "LOCAL(" ) <name> ")" (("=" <expression>) | ("[<expression>]" ("={" <expression> ("," <expression>)* "}")?) | ("[]={" <expression> ("," <expression>)* "}"))? ";"
cppNode* micpp::_local(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppLocal* ret = NULL;
	if(Token(info, TYPE_STRING, "LOCAL") && Token(info, TYPE_SYMBOL, "("))
	{
		ret = new cppLocal(this, info.line);
		if(Token(info, TYPE_STRING) == false)
			goto _LOCAL_ERROR;

		strcpy(ret->name[0], info.token);
		if(Token(info, TYPE_SYMBOL, ")") == false)
			goto _LOCAL_ERROR;

		if(Token(info, TYPE_SYMBOL, "="))
		{
			ret->op = new cppVariable(this, info.line);
			((cppVariable*)ret->op)->v = 0;

			ret->size = 1;
			ret->node = new cppNode*[1];

			ret->node[0] = _expression(info);
			if(ret->node[0] == NULL)
				goto _LOCAL_ERROR;
		}
		else if(Token(info, TYPE_SYMBOL, "["))
		{
			if(Token(info, TYPE_SYMBOL, "]") == false)
			{
				ret->op = _expression(info);
				if(Token(info, TYPE_SYMBOL, "]") == false)
					goto _LOCAL_ERROR;
			}

			if(Token(info, TYPE_SYMBOL, "="))
			{
				if(Token(info, TYPE_SYMBOL, "{") == false)
					goto _LOCAL_ERROR;

				std::list<cppNode*> nodelist;
				for(ret->size = 0;;)
				{
					cppNode* node = _expression(info);

					if(node == NULL || info.error)
					{
						for(std::list<cppNode*>::iterator it = nodelist.begin(); it != nodelist.end(); ++it)
							delete *it;

						goto _LOCAL_ERROR;
					}
					else
					{
						nodelist.push_back(node);
						++ret->size;
					}

					if(Token(info, TYPE_SYMBOL, ",") == false)
						break;
				}

				if(ret->size <= 0)
					goto _LOCAL_ERROR;

				ret->node = new cppNode*[ret->size];
				std::list<cppNode*>::iterator it = nodelist.begin();
				for(int i=0; i < ret->size; ++i)
				{
					ret->node[i] = *it;
					++it;
				}

				if(info.error || Token(info, TYPE_SYMBOL, "}") == false)
					goto _LOCAL_ERROR;
			}

			if(ret->op == NULL)
			{
				if(ret->size > 0)
				{
					ret->op = new cppVariable(this, info.line);
					((cppVariable*)ret->op)->v = ret->size;
				}
				else
				{
					goto _LOCAL_ERROR;
				}
			}
		}
		else
		{
			ret->op = new cppVariable(this, info.line);
			((cppVariable*)ret->op)->v = 0;
		}

		if(Token(info, TYPE_SYMBOL, ";"))
			return ret;

_LOCAL_ERROR:
		info.error = true;
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "local format error");
		micpp::PRINT(micpp::STRING);
		delete ret;
	}

	return NULL;
}

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
cppNode* micpp::_function(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	int num;

	if(Token(info, TYPE_STRING, "FUNCTION0"))
		num = 0;
	else if(Token(info, TYPE_STRING, "FUNCTION1"))
		num = 1;
	else if(Token(info, TYPE_STRING, "FUNCTION2"))
		num = 2;
	else if(Token(info, TYPE_STRING, "FUNCTION3"))
		num = 3;
	else if(Token(info, TYPE_STRING, "FUNCTION4"))
		num = 4;
	else if(Token(info, TYPE_STRING, "FUNCTION5"))
		num = 5;
	else if(Token(info, TYPE_STRING, "FUNCTION6"))
		num = 6;
	else if(Token(info, TYPE_STRING, "FUNCTION7"))
		num = 7;
	else if(Token(info, TYPE_STRING, "FUNCTION8"))
		num = 8;
	else if(Token(info, TYPE_STRING, "FUNCTION9"))
		num = 9;
	else
		return NULL;

	cppFunction* ret = new cppFunction(this, info.line);
	std::map<std::string, cppNode*>::iterator it = nodemap.end();
	bool check = false;

	if(Token(info, TYPE_SYMBOL, "(") == false)
		goto _FUNCTION_ERROR;

	if(Token(info, TYPE_STRING) == false)
		goto _FUNCTION_ERROR;

	it = nodemap.find(info.token);
	if(it != nodemap.end())
	{
		if(it->second->Interface() != cppNode::NODE_FUNCTION)
			goto _FUNCTION_ERROR;

		delete ret;
		ret = (cppFunction*)it->second;
	}
	else
	{
		strcpy(ret->name[micpp::MAX_PARAM], info.token);
		nodemap.insert(std::pair<std::string, cppNode*>(ret->name[micpp::MAX_PARAM], ret));
	}

	for(int i=0; i < num; ++i)
	{
		if(Token(info, TYPE_SYMBOL, ",") == false || Token(info, TYPE_STRING) == false)
			goto _FUNCTION_ERROR;

		if(it != nodemap.end() && ret->name[i][0] == '\0')
			goto _FUNCTION_ERROR;

		strcpy(ret->name[i], info.token);

		if(Token(info, TYPE_SYMBOL, "="))
		{
			if(ret->node[i] != NULL)
				goto _FUNCTION_ERROR;

			ret->node[i] = _expression(info);
			check = true;
		}

		if(check && ret->node[i] == NULL)
			goto _FUNCTION_ERROR;
	}

	if(ret->name[num][0] != '\0' || Token(info, TYPE_SYMBOL, ")") == false)
		goto _FUNCTION_ERROR;

	if(Token(info, TYPE_SYMBOL, ";"))
	{
		if(ret->node[micpp::MAX_PARAM])
			goto _FUNCTION_ERROR;

		return ret;
	}

	if(ret->node[micpp::MAX_PARAM])
		goto _FUNCTION_ERROR;
	else
		ret->node[micpp::MAX_PARAM] = _block(info);

	if(info.error || ret->node[micpp::MAX_PARAM] == NULL)
		goto _FUNCTION_ERROR;

	if(info.fp)
		fprintf(info.fp, "\t\t_cpp->RegFun(\"%s\", %s);\r\n", ret->name[micpp::MAX_PARAM], ret->name[micpp::MAX_PARAM]);

	return ret;

_FUNCTION_ERROR:
	nodemap.erase(nodemap.find(ret->name[micpp::MAX_PARAM]));

	info.error = true;
	sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "function format error");
	micpp::PRINT(micpp::STRING);
	delete ret;
	return NULL;
}

//<if>				-> "if(" <expression> ")" <block> | <line> ("else if(" <expression> ")" <block> | <line>)* ("else" <block> | <line>)?
cppNode* micpp::_if(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppCondition* ret = NULL;
	if(Token(info, TYPE_STRING, "if"))
	{
		ret = new cppCondition(this, info.line);

		if(Token(info, TYPE_SYMBOL, "(") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss (");
			micpp::PRINT(micpp::STRING);
			goto _IF_ERROR;
		}

		ret->op = _expression(info);

		if(ret->op == NULL)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss expression");
			micpp::PRINT(micpp::STRING);
			goto _IF_ERROR;
		}

		if(Token(info, TYPE_SYMBOL, ")") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss )");
			micpp::PRINT(micpp::STRING);
			goto _IF_ERROR;
		}

		ret->block = _block(info);
		if(ret->block == NULL)
			ret->block = _line(info);

		if(ret->block == NULL)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss body");
			micpp::PRINT(micpp::STRING);
			goto _IF_ERROR;
		}

		for(cppCondition* p = ret; Token(info, TYPE_STRING, "else");)
		{
			p->next = new cppCondition(this, info.line);
			p = (cppCondition*)p->next;

			if(Token(info, TYPE_STRING, "if"))
			{
				if(Token(info, TYPE_SYMBOL, "(") == false)
				{
					sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss (");
					micpp::PRINT(micpp::STRING);
					goto _IF_ERROR;
				}

				p->op = _expression(info);

				if(p->op == NULL)
				{
					sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss expression");
					micpp::PRINT(micpp::STRING);
					goto _IF_ERROR;
				}

				if(Token(info, TYPE_SYMBOL, ")") == false)
				{
					sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss )");
					micpp::PRINT(micpp::STRING);
					goto _IF_ERROR;
				}
			}

			p->block = _block(info);
			if(p->block == NULL)
				p->block = _line(info);

			if(p->block == NULL)
			{
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss body");
				micpp::PRINT(micpp::STRING);
				goto _IF_ERROR;
			}

			if(p->op == NULL)
				break;
		}

		return ret;

_IF_ERROR:
		info.error = true;
		delete ret;
	}

	return NULL;
}

//<for>				-> "for(" (<global> | <locla> | (<expression>)? ";") (<expression>) ";" <expression> ")" <block> | <line>
cppNode* micpp::_for(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppLoop* ret = NULL;
	cppNode* init = NULL;

	if(Token(info, TYPE_STRING, "for"))
	{
		ret = new cppLoop(this, info.line);

		if(Token(info, TYPE_SYMBOL, "(") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss (");
			micpp::PRINT(micpp::STRING);
			goto _FOR_ERROR;
		}

		init = _global(info, false);

		if(init == NULL)
			init = _local(info);

		if(init == NULL)
		{
			init = _expression(info);
			if(Token(info, TYPE_SYMBOL, ";") == false)
			{
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
				micpp::PRINT(micpp::STRING);
				goto _FOR_ERROR;
			}
		}

		ret->condition = _expression(info);
		if(Token(info, TYPE_SYMBOL, ";") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
			micpp::PRINT(micpp::STRING);
			goto _FOR_ERROR;
		}

		ret->loop = _expression(info);
		if(Token(info, TYPE_SYMBOL, ")") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss )");
			micpp::PRINT(micpp::STRING);
			goto _FOR_ERROR;
		}

		ret->block = _block(info);
		if(ret->block == NULL)
			ret->block = _line(info);

		if(ret->block == NULL)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss body");
			micpp::PRINT(micpp::STRING);
			goto _FOR_ERROR;
		}

		if(ret->condition == NULL)
		{
			ret->condition = new cppVariable(this, info.line);
			((cppVariable*)ret->condition)->v = 1;
		}

		if(ret->loop == NULL)
			ret->loop = new cppNode(this, info.line);

		if(init)
		{
			cppBlock* block = new cppBlock(this, info.line);
			block->node.push_back(init);
			block->node.push_back(ret);
			return block;
		}

		return ret;

_FOR_ERROR:
		info.error = true;
		delete ret;
	}

	return NULL;
}

//<block>			-> "{" (<block> | <global> | <local> | (("return")? <expression> ";") | <if> | <for> | "break;" | "continue;")* "}"
cppNode* micpp::_block(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppBlock* ret = NULL;
	if(Token(info, TYPE_SYMBOL, "{"))
	{
		ret = new cppBlock(this, info.line);
		std::map<std::string, variable*> var;

		do
		{
			cppNode* node;
			node = _block(info);
			if(node)
			{
				ret->node.push_back(node);
				continue;
			}

			node = _if(info);
			if(node)
			{
				ret->node.push_back(node);
				continue;
			}

			node = _for(info);
			if(node)
			{
				ret->node.push_back(node);
				continue;
			}

			node = _global(info, false);
			if(node)
			{
				ret->node.push_back(node);

				if(var.find(((cppGlobal*)node)->name[0]) != var.end())
				{
					sprintf(micpp::STRING, "micpp %s(%d) : \"%s\" redefine\n", name, info.line, ((cppGlobal*)node)->name[0]);
					micpp::PRINT(micpp::STRING);
					goto _BLOCK_ERROR;
				}
				else
				{
					var.insert(std::pair<std::string, variable*>(((cppGlobal*)node)->name[0], (micpp::variable*)NULL));
				}
				continue;
			}

			node = _local(info);
			if(node)
			{
				ret->node.push_back(node);

				if(var.find(((cppLocal*)node)->name[0]) != var.end())
				{
					sprintf(micpp::STRING, "micpp %s(%d) : \"%s\" redefine\n", name, info.line, ((cppLocal*)node)->name[0]);
					micpp::PRINT(micpp::STRING);
					goto _BLOCK_ERROR;
				}
				else
				{
					var.insert(std::pair<std::string, variable*>(((cppLocal*)node)->name[0], (micpp::variable*)NULL));
				}
				continue;
			}

			if(Token(info, TYPE_STRING, "break"))
			{
				if(Token(info, TYPE_SYMBOL, ";") == false)
				{
					sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
					micpp::PRINT(micpp::STRING);
					goto _BLOCK_ERROR;
				}

				node = new cppFlow(this, info.line);
				((cppFlow*)node)->v = cppFlow::FLOW_BREAK;
				ret->node.push_back(node);
				continue;
			}

			if(Token(info, TYPE_STRING, "continue"))
			{
				if(Token(info, TYPE_SYMBOL, ";") == false)
				{
					sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
					micpp::PRINT(micpp::STRING);
					goto _BLOCK_ERROR;
				}

				node = new cppFlow(this, info.line);
				((cppFlow*)node)->v = cppFlow::FLOW_CONTINUE;
				ret->node.push_back(node);
				continue;
			}

			cppReturn* r = Token(info, TYPE_STRING, "return") ? new cppReturn(this, info.line) : NULL;
			node = _expression(info);
			if(node)
			{
				if(r)
				{
					r->op = node;
					node = r;
				}
				ret->node.push_back(node);

				if(Token(info, TYPE_SYMBOL, ";") == false)
				{
					sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
					micpp::PRINT(micpp::STRING);
					goto _BLOCK_ERROR;
				}
				continue;
			}
			else if(r)
			{
				delete r;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss expression");
				micpp::PRINT(micpp::STRING);
				goto _BLOCK_ERROR;
			}

			if(Token(info, TYPE_SYMBOL, ";"))
				continue;

			if(Token(info, TYPE_SYMBOL, "}"))
				break;

			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "unknown in block");
			micpp::PRINT(micpp::STRING);
			goto _BLOCK_ERROR;
		}
		while(!info.error);
	}

	return ret;

_BLOCK_ERROR:
	info.error = true;
	delete ret;
	return NULL;
}

//<line>			-> ("return")? <expression> ";") | <if> | <for> | break | continue
cppNode* micpp::_line(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppBlock* ret = new cppBlock(this, info.line);
	std::map<std::string, variable*> var;

	cppReturn* r = NULL;

	cppNode* node;
	node = _if(info);
	if(node)
	{
		ret->node.push_back(node);
		return ret;
	}

	node = _for(info);
	if(node)
	{
		ret->node.push_back(node);
		return ret;
	}

	if(Token(info, TYPE_STRING, "break"))
	{
		if(Token(info, TYPE_SYMBOL, ";") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
			micpp::PRINT(micpp::STRING);
			goto _LINE_ERROR;
		}

		node = new cppFlow(this, info.line);
		((cppFlow*)node)->v = cppFlow::FLOW_BREAK;
		ret->node.push_back(node);
		return ret;
	}

	if(Token(info, TYPE_STRING, "continue"))
	{
		if(Token(info, TYPE_SYMBOL, ";") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
			micpp::PRINT(micpp::STRING);
			goto _LINE_ERROR;
		}

		node = new cppFlow(this, info.line);
		((cppFlow*)node)->v = cppFlow::FLOW_CONTINUE;
		ret->node.push_back(node);
		return ret;
	}

	r = Token(info, TYPE_STRING, "return") ? new cppReturn(this, info.line) : NULL;
	node = _expression(info);
	if(node)
	{
		if(r)
		{
			r->op = node;
			node = r;
		}
		ret->node.push_back(node);

		if(Token(info, TYPE_SYMBOL, ";") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ;");
			micpp::PRINT(micpp::STRING);
			goto _LINE_ERROR;
		}
		return ret;
	}
	else if(r)
	{
		delete r;
		sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss expression");
		micpp::PRINT(micpp::STRING);
		goto _LINE_ERROR;
	}

	if(Token(info, TYPE_SYMBOL, ";"))
		return ret;

	sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "unknown in line");
	micpp::PRINT(micpp::STRING);

_LINE_ERROR:
	info.error = true;
	delete ret;
	return NULL;
}

//<expression>		-> <layer0> ("=" <layer0>)*
cppNode* micpp::_expression(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer0(info);
	if(ret && Token(info, TYPE_SYMBOL, "="))
	{
		cppOperator* op = new cppOperator(this, info.line);
		op->op = cppNode::SYMBOL_ASSIGNMENT;
		op->left = ret;
		ret = op;

		op->right = _layer0(info);
		if(op->right == NULL)
		{
			info.error = true;
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
			micpp::PRINT(micpp::STRING);
			delete ret;
			return NULL;
		}

		while(Token(info, TYPE_SYMBOL, "="))
		{
			cppNode* n = op->right;
			op->right = new cppOperator(this, info.line);
			op = (cppOperator*)op->right;
			op->op = cppNode::SYMBOL_ASSIGNMENT;
			op->left = n;

			op->right = _layer0(info);
			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}
	}

	return ret;
}

//<layer0>			-> <layer1> ("||" <layer1>)*
cppNode* micpp::_layer0(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer1(info);
	if(ret)
	{
		while(Token(info, TYPE_SYMBOL, "||"))
		{
			cppOperator* op = new cppOperator(this, info.line);
			op->op = cppNode::SYMBOL_OR;
			op->left = ret;
			op->right = _layer1(info);
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}
	}

	return ret;
}

//<layer1>			-> <layer2> ("&&" <layer2>)*
cppNode* micpp::_layer1(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer2(info);
	if(ret)
	{
		while(Token(info, TYPE_SYMBOL, "&&"))
		{
			cppOperator* op = new cppOperator(this, info.line);
			op->op = cppNode::SYMBOL_AND;
			op->left = ret;
			op->right = _layer2(info);
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}
	}

	return ret;
}

//<layer2>			-> <layer3> (("==" | "!=") <layer3>)*
cppNode* micpp::_layer2(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer3(info);
	if(ret)
	{
		while(Token(info, TYPE_SYMBOL, "==") || Token(info, TYPE_SYMBOL, "!="))
		{
			cppOperator* op = new cppOperator(this, info.line);

			if(!strcmp(info.token, "=="))
				op->op = cppNode::SYMBOL_E;
			else if(!strcmp(info.token, "!="))
				op->op = cppNode::SYMBOL_NE;

			op->left = ret;
			op->right = _layer3(info);
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}
	}

	return ret;
}

//<layer3>			-> <layer4> (("<" | "<=" | ">" | ">=") <layer4>)*
cppNode* micpp::_layer3(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer4(info);
	if(ret)
	{
		while(Token(info, TYPE_SYMBOL, "<") || Token(info, TYPE_SYMBOL, "<=") || Token(info, TYPE_SYMBOL, ">") || Token(info, TYPE_SYMBOL, ">="))
		{
			cppOperator* op = new cppOperator(this, info.line);

			if(!strcmp(info.token, "<"))
				op->op = cppNode::SYMBOL_L;
			else if(!strcmp(info.token, "<="))
				op->op = cppNode::SYMBOL_LE;
			else if(!strcmp(info.token, ">"))
				op->op = cppNode::SYMBOL_G;
			else if(!strcmp(info.token, ">="))
				op->op = cppNode::SYMBOL_GE;

			op->left = ret;
			op->right = _layer4(info);
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}
	}

	return ret;
}

//<layer4>			-> <layer5> (("+" | "-") <layer5>)*
cppNode* micpp::_layer4(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer5(info);
	if(ret)
	{
		while(Token(info, TYPE_SYMBOL, "+") || Token(info, TYPE_SYMBOL, "-"))
		{
			cppOperator* op = new cppOperator(this, info.line);

			if(!strcmp(info.token, "+"))
				op->op = cppNode::SYMBOL_ADD;
			else if(!strcmp(info.token, "-"))
				op->op = cppNode::SYMBOL_SUB;

			op->left = ret;
			op->right = _layer5(info);
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}

			ret = OptimizeExpression((cppOperator*)ret, this, info.line);
		}
	}

	return ret;
}

//<layer5>			-> <layer6> (("*" | "/" | "%") <layer6>)*
cppNode* micpp::_layer5(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	cppNode* ret = _layer6(info);
	if(ret)
	{
		while(Token(info, TYPE_SYMBOL, "*") || Token(info, TYPE_SYMBOL, "/") || Token(info, TYPE_SYMBOL, "%"))
		{
			cppOperator* op = new cppOperator(this, info.line);

			if(!strcmp(info.token, "*"))
				op->op = cppNode::SYMBOL_MUL;
			else if(!strcmp(info.token, "/"))
				op->op = cppNode::SYMBOL_DIV;
			else if(!strcmp(info.token, "%"))
				op->op = cppNode::SYMBOL_MOD;

			op->left = ret;
			op->right = _layer6(info);
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}

			ret = OptimizeExpression((cppOperator*)ret, this, info.line);
		}
	}

	return ret;
}

//<layer6>			-> ("!" | "+" | "-" | "&") <layer6>
//					-> "(" <expression> ")"
//					-> (number("." number "f")?) | ("0x"number)
//					-> ("L") "'" ("\")? <char> "'"
//					-> ((name) "::" )name?(( "(" (<expression> ("," <expression>)*) ")") | ("[" <expression> "]"))*
cppNode* micpp::_layer6(CompilerInfo& info)
{
	if(info.error)
		return NULL;

	if(Token(info, TYPE_SYMBOL, "!") || Token(info, TYPE_SYMBOL, "+") || Token(info, TYPE_SYMBOL, "-") || Token(info, TYPE_SYMBOL, "&"))
	{
		cppOperator* ret = new cppOperator(this, info.line);

		if(!strcmp(info.token, "!"))
		{
			ret->op = cppNode::SYMBOL_NOT;
		}
		else if(!strcmp(info.token, "+"))
		{
			ret->op = cppNode::SYMBOL_ADD;
		}
		else if(!strcmp(info.token, "-"))
		{
			ret->op = cppNode::SYMBOL_SUB;
		}
		else if(!strcmp(info.token, "&"))
		{
			ret->op = cppNode::SYMBOL_ADDRESS;
		}

		ret->left = _layer6(info);
		if(ret->left == NULL)
		{
			info.error = true;
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss right");
			micpp::PRINT(micpp::STRING);
			delete ret;
			return NULL;
		}

		return (ret->op == cppNode::SYMBOL_ADD || ret->op == cppNode::SYMBOL_SUB) ? OptimizeExpression(ret, this, info.line) : ret;
	}
	else if(Token(info, TYPE_SYMBOL, "("))
	{
		cppNode* ret = _expression(info);
		if(ret && Token(info, TYPE_SYMBOL, ")") == false)
		{
			info.error = true;
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss )");
			micpp::PRINT(micpp::STRING);
			delete ret;
			return NULL;
		}

		return ret;
	}
	else if(Token(info, TYPE_NUMBER))
	{
		cppVariable* ret = new cppVariable(this, info.line);
		strcpy(ret->name[0], info.token);

		if(!strcmp(ret->name[0], "0") && Token(info, TYPE_UNKNOWN, "x"))
		{
			strcat(ret->name[0], info.token);

			while(Token(info, TYPE_NUMBER)
				  || Token(info, TYPE_UNKNOWN, "A")
				  || Token(info, TYPE_UNKNOWN, "B")
				  || Token(info, TYPE_UNKNOWN, "C")
				  || Token(info, TYPE_UNKNOWN, "D")
				  || Token(info, TYPE_UNKNOWN, "E")
				  || Token(info, TYPE_UNKNOWN, "F")
				  || Token(info, TYPE_UNKNOWN, "a")
				  || Token(info, TYPE_UNKNOWN, "b")
				  || Token(info, TYPE_UNKNOWN, "c")
				  || Token(info, TYPE_UNKNOWN, "d")
				  || Token(info, TYPE_UNKNOWN, "e")
				  || Token(info, TYPE_UNKNOWN, "f"))
			{
				strcat(ret->name[0], info.token);
			}

			//int
			ret->v.ptr = (micpp::variable*)(INT_T)(int)strtoul(ret->name[0], NULL, 0);
			strcpy(ret->name[1], "i");
		}
		else if(Token(info, TYPE_SYMBOL, "."))
		{
			strcat(ret->name[0], ".");
			if(Token(info, TYPE_NUMBER))
			{
				strcat(ret->name[0], info.token);
			}
			else
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss number");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}

			if(Token(info, TYPE_STRING, "f"))
			{
				strcat(ret->name[0], "f");
			}
			else
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss \'f\'");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}

			//f32
			ret->v = atof(ret->name[0]);
		}
		else if(ret->name[0][0] == '0' && ret->name[0][1] != '\0')
		{
			info.error = true;
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "number format error");
			micpp::PRINT(micpp::STRING);
			delete ret;
			return NULL;
		}
		else
		{
			//int
			ret->v.ptr = (micpp::variable*)(INT_T)(int)strtoul(ret->name[0], NULL, 0);
			strcpy(ret->name[1], "i");
		}

		ret->name[0][0] = '\0';
		return ret;
	}
	else if((Token(info, TYPE_STRING, "L") && Token(info, TYPE_SYMBOL, "\'") && strcpy(info.token, "L")) || Token(info, TYPE_SYMBOL, "\'"))
	{
		cppVariable* ret = new cppVariable(this, info.line);
		bool convert = (info.token[0] == 'L');

		if(Token(info, TYPE_UNKNOWN, " "))
		{
			ret->v = info.token[0];
		}
		else if(Token(info, TYPE_SYMBOL, "\\"))
		{
			if(Token(info, TYPE_UNKNOWN))
			{
				switch(info.token[0])
				{
				case '0':
					ret->v = 0;
					break;
				case 'a':
					ret->v = 7;
					break;
				case 'b':
					ret->v = 8;
					break;
				case 't':
					ret->v = 9;
					break;
				case 'n':
					ret->v = 10;
					break;
				case 'v':
					ret->v = 11;
					break;
				case 'f':
					ret->v = 12;
					break;
				case 'r':
					ret->v = 13;
					break;
				case '\\':
					ret->v = '\\';
					break;
				default:
					info.error = true;
				}
			}
			else
			{
				info.error = true;
			}
		}
		else if(Token(info, TYPE_UNKNOWN))
		{
			ret->v = info.token[0];
		}
		else
		{
			info.error = true;
		}

		if(info.error)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "unknown char");
			micpp::PRINT(micpp::STRING);
			delete ret;
			return NULL;
		}
		else if(Token(info, TYPE_SYMBOL, "\'") == false)
		{
			sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss \'");
			micpp::PRINT(micpp::STRING);
			delete ret;
			return NULL;
		}

		//int
		ret->v.ptr = (micpp::variable*)(INT_T)(int)ret->v;
		strcpy(ret->name[1], "i");

		return ret;
	}
	else if(Token(info, TYPE_SYMBOL, "::") || Token(info, TYPE_STRING))
	{
		cppNode* ret = new cppVariable(this, info.line);

		if(!strcmp(info.token, "::"))
		{
			strcpy(((cppVariable*)ret)->name[1], "micpp");

			if(Token(info, TYPE_STRING) == false)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss name");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}

		strcpy(((cppVariable*)ret)->name[0], info.token);

		if(((cppVariable*)ret)->name[1][0] == '\0' && Token(info, TYPE_SYMBOL, "::"))
		{
			if(Token(info, TYPE_STRING))
			{
				strcpy(((cppVariable*)ret)->name[1], ((cppVariable*)ret)->name[0]);
				strcpy(((cppVariable*)ret)->name[0], info.token);
			}
			else
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss name");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}

		while(Token(info, TYPE_SYMBOL, "(") || Token(info, TYPE_SYMBOL, "["))
		{
			cppOperator* op = new cppOperator(this, info.line);

			if(!strcmp(info.token, "("))
			{
				op->op = cppNode::SYMBOL_ROUND_L;
				op->right = new cppParam(this, info.line);

				do
				{
					if((((cppParam*)op->right)->node[((cppParam*)op->right)->num] = _expression(info)) != NULL)
					{
						((cppParam*)op->right)->num += 1;

						if(!Token(info, TYPE_SYMBOL, ","))
							break;
					}
					else
					{
						break;
					}
				}
				while(((cppParam*)op->right)->num < micpp::MAX_PARAM);
			}
			else if(!strcmp(info.token, "["))
			{
				op->op = cppNode::SYMBOL_SQARE_L;
				op->right = _expression(info);
			}

			op->left = ret;
			ret = op;

			if(op->right == NULL)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "unknown symbol");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}

			if(op->op == cppNode::SYMBOL_ROUND_L && Token(info, TYPE_SYMBOL, ")") == false)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss )");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
			else if(op->op == cppNode::SYMBOL_SQARE_L && Token(info, TYPE_SYMBOL, "]") == false)
			{
				info.error = true;
				sprintf(micpp::STRING, "micpp %s(%d) : %s\n", name, info.line, "miss ]");
				micpp::PRINT(micpp::STRING);
				delete ret;
				return NULL;
			}
		}

		return ret;
	}

	return NULL;
}
