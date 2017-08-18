#pragma once
#ifndef _H02_
#define _H02_

#define M_PI  3.14159265358979323846	//圆周率


void eatSpaces(char* str);
double expr(const char* str);
double term(const char* str, size_t& index);
double number(const char* str, size_t& index);
char* extract(const char* str, size_t& index);
double doOperation(char* op, double value);

const double DEG_TO_RAD{ M_PI / 180 };	//弧度转角度的常量

/**
* \字符串去空格
* \param str
*/
inline void eatSpaces(char* str)
{
	size_t i{};
	size_t j{};

	while ((*(str + i) = *(str + j++)) != '\0')
		if (*(str + i) != ' ')
			i++;
}


/**
* \计算表达式的值
* \param str
* \return
*/
inline double expr(const char* str)
{
	double value{};	//定义返回值
	size_t index{};	//定义索引

	value = term(str, index);	//取一个项值

	for (;;)
	{
		switch (*(str + index++))
		{
		case '\0':				//表达式结束
			return value;
		case '+':				//加运算
			value += term(str, index);
			break;
		case '-':				//减运算
			value -= term(str, index);
			break;
		default:
			char message[20]{"非法表达式字符："};
			strncat_s(message, str + index - 1, 1);
			throw message;
			break;
		}
	}

}

/**
* \计算一项的值
* \param str
* \param index
* \return
*/
inline double term(const char* str, size_t& index)
{
	double value{};	//定义返回值

	value = number(str, index);	//取数字

	while (true)
	{
		if (*(str + index) == '*')	//乘法
			value *= number(str, ++index);
		else if (*(str + index) == '/')	//除法
			value /= number(str, ++index);
		else
			break;
	}

	return value;
}

/**
* \取数
* \param str
* \param index
* \return
*/
inline double number(const char* str, size_t& index)
{
	double value{};	//定义返回值

	//找出数学函数名
	char op[6];
	int ip{};
	while (isalpha(*(str + index)))                // Copy the function name
		op[ip++] = *(str + index++);
	op[ip] = '\0';

	if (*(str+index)=='(')	//处理括号
	{
		char* psubstr{};
		psubstr = extract(str, ++index);	//取括号内子串
		value = expr(psubstr);	//返回子串表达式结果

		if (op[0])		//有数学函数则执行函数
			value = doOperation(op, value);

		delete[]psubstr;	//释放请求的内存
		return value;
	}

	if (!isdigit(*(str + index)))
	{
		char message[20]{"非法数字字符："};
		strncat_s(message, str + index, 1);
		throw message;
	}

	while (isdigit(*(str + index)))	//整数位,从高到低
		value = 10 * value + (*(str + index++) - '0');

	if (*(str + index) != '.')
		return value;

	double factor{ 1.0 };
	while (isdigit(*(str + (++index))))	//小数位
	{
		factor *= 0.1;
		value = value + (*(str + index) - '0')*factor;
	}

	return value;
}

/**
 * \取括号内子字符串
 * \param str 
 * \param index 
 * \return 
 */
inline char* extract(const char* str, size_t& index)
{
	char* pstr{};	//定义返回字符串指针
	size_t numL{};	//定义左括号数量
	size_t bufindex{ index };	//保存起始索引

	do
	{
		switch (*(str+index))
		{
		case ')':
			if (0 == numL)
			{
				++index;
				pstr = new char[index - bufindex];
				if (!pstr)
					throw"内存请求失败";
				//复制子串
				strncpy_s(pstr, index - bufindex, str + bufindex, index - bufindex - 1);

				return pstr;
			}
			else
				numL--;
			break;
		case '(':
			numL++;
			break;
		}
	}
	while (*(str+index++)!='\0');

	throw "括号不成对，一定是出错了";
}

/**
 * \执行数学函数
 * \param op 
 * \param value 
 * \return 
 */
double doOperation(char* op, double value)
{
	if (!_stricmp(op, "sin"))
		return sin(value);
	else if (!_stricmp(op, "sind"))
		return sin(value*DEG_TO_RAD);
	else if (!_stricmp(op, "cos"))
		return cos(value);
	else if (!_stricmp(op, "cosd"))
		return cos(value*DEG_TO_RAD);
	else if (!_stricmp(op, "tan"))
		return tan(value);
	else if (!_stricmp(op, "tand"))
		return tan(value*DEG_TO_RAD);
	else if (!_stricmp(op, "sqrt"))
		return sqrt(value);
	else
	{
		char message[20]{"不认识的函数："};
		strncat_s(message, op, 6);
		throw message;
	}
	return 0;
}


#endif //_H02_
