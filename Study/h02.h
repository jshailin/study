#pragma once
#ifndef _H02_
#define _H02_

#define M_PI  3.14159265358979323846	//Բ����


void eatSpaces(char* str);
double expr(const char* str);
double term(const char* str, size_t& index);
double number(const char* str, size_t& index);
char* extract(const char* str, size_t& index);
double doOperation(char* op, double value);

const double DEG_TO_RAD{ M_PI / 180 };	//����ת�Ƕȵĳ���

/**
* \�ַ���ȥ�ո�
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
* \������ʽ��ֵ
* \param str
* \return
*/
inline double expr(const char* str)
{
	double value{};	//���巵��ֵ
	size_t index{};	//��������

	value = term(str, index);	//ȡһ����ֵ

	for (;;)
	{
		switch (*(str + index++))
		{
		case '\0':				//���ʽ����
			return value;
		case '+':				//������
			value += term(str, index);
			break;
		case '-':				//������
			value -= term(str, index);
			break;
		default:
			char message[20]{"�Ƿ����ʽ�ַ���"};
			strncat_s(message, str + index - 1, 1);
			throw message;
			break;
		}
	}

}

/**
* \����һ���ֵ
* \param str
* \param index
* \return
*/
inline double term(const char* str, size_t& index)
{
	double value{};	//���巵��ֵ

	value = number(str, index);	//ȡ����

	while (true)
	{
		if (*(str + index) == '*')	//�˷�
			value *= number(str, ++index);
		else if (*(str + index) == '/')	//����
			value /= number(str, ++index);
		else
			break;
	}

	return value;
}

/**
* \ȡ��
* \param str
* \param index
* \return
*/
inline double number(const char* str, size_t& index)
{
	double value{};	//���巵��ֵ

	//�ҳ���ѧ������
	char op[6];
	int ip{};
	while (isalpha(*(str + index)))                // Copy the function name
		op[ip++] = *(str + index++);
	op[ip] = '\0';

	if (*(str+index)=='(')	//��������
	{
		char* psubstr{};
		psubstr = extract(str, ++index);	//ȡ�������Ӵ�
		value = expr(psubstr);	//�����Ӵ����ʽ���

		if (op[0])		//����ѧ������ִ�к���
			value = doOperation(op, value);

		delete[]psubstr;	//�ͷ�������ڴ�
		return value;
	}

	if (!isdigit(*(str + index)))
	{
		char message[20]{"�Ƿ������ַ���"};
		strncat_s(message, str + index, 1);
		throw message;
	}

	while (isdigit(*(str + index)))	//����λ,�Ӹߵ���
		value = 10 * value + (*(str + index++) - '0');

	if (*(str + index) != '.')
		return value;

	double factor{ 1.0 };
	while (isdigit(*(str + (++index))))	//С��λ
	{
		factor *= 0.1;
		value = value + (*(str + index) - '0')*factor;
	}

	return value;
}

/**
 * \ȡ���������ַ���
 * \param str 
 * \param index 
 * \return 
 */
inline char* extract(const char* str, size_t& index)
{
	char* pstr{};	//���巵���ַ���ָ��
	size_t numL{};	//��������������
	size_t bufindex{ index };	//������ʼ����

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
					throw"�ڴ�����ʧ��";
				//�����Ӵ�
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

	throw "���Ų��ɶԣ�һ���ǳ�����";
}

/**
 * \ִ����ѧ����
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
		char message[20]{"����ʶ�ĺ�����"};
		strncat_s(message, op, 6);
		throw message;
	}
	return 0;
}


#endif //_H02_
