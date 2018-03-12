#pragma once
#include <iostream>
#include <cmath>
#include "Stack.h"

//helpful functions
bool isAlpha(char item)
{
	int codeItem = item;
	int codeUpperA = 65;
	int codeLowerA = 97;
	int codeUpperZ = 90;
	int codeLowerZ = 122;

	return ((codeUpperA <= codeItem && codeItem <= codeUpperZ)
		|| (codeLowerA <= codeItem && codeItem <= codeLowerZ));
}

bool isNumber(char item)
{
	int codeItem = item;
	int code0 = 48;
	int code9 = 57;
	return (code0 <= codeItem && codeItem <= code9);
}

bool isVariable(char item)
{
	return (isNumber(item) || isAlpha(item));
}

bool isOperation(char item)
{
	return (item == '+' || item == '-' ||
		item == '/' || item == '*' ||
		item == '^');
}

bool isOpeningBracket(char item)
{
	return (item == '(' || item == '[' || item == '{');
}

bool isClosingBracket(char item)
{
	return (item == ')' || item == ']' || item == '}');
}

bool isBracket(char item)
{
	return (isOpeningBracket(item) || isClosingBracket(item));
}

int numberOfBrackets(const char* str, int length)
{
	int check = 0;
	for (int i = 0; i < length; i++)
		if (isBracket(str[i]))
			check++;

	return check;
}

int operationPriority(char item)
{
	if (isOpeningBracket(item))
		return 0;

	if (item == '+' || item == '-')
		return 1;

	if (item == '/' || item == '*')
		return 2;

	if (item == '^')
		return 3;

	return -1;
}

int countingValue(int item1, int item2, char operand)
{
	if (operand == '-')
		return item1 - item2;
	else if (operand == '+')
		return item1 + item2;
	else if (operand == '/')
		return item1 / item2;
	else if (operand == '*')
		return item1 * item2;
	else
		return pow(item1, item2);
}

//main functions

bool isBracketsClosed(const char* str)
{
	Stack<char> stack;
	int length = strlen(str);
	char temp;
	bool doNothing = NULL;

	for (int i = 0; i < length; i++)
	{
		if (isOpeningBracket(str[i]))
			stack.push(str[i]);
		else if (isClosingBracket(str[i])) {
			if (stack.isStackEmpty())
				return false;

			temp = stack.pop();
			if ((temp == '(' && str[i] == ')') ||
				(temp == '{' && str[i] == '}') ||
				(temp == '[' && str[i] == ']'))
				doNothing;
			else
				return false;
		}
	}

	return stack.isStackEmpty();
}

//it's very hard to read
//do you really want to do this?
//Надо ли результирующую
void conversionToReversePolishEntry(const char* str, char* strResult)
{
	if (!isBracketsClosed(str))
		throw "Brackets!!!";

	Stack<int> stack;

	int length = strlen(str);

	int priorityTemp;
	int prioriryStr;
	int iRes = 0;
	char temp;

	for (int i = 0; i < length; i++)
	{
		if (isVariable(str[i]))
			strResult[iRes++] = str[i];

		else if (isOpeningBracket(str[i]))
			stack.push(str[i]);

		else if (isOperation(str[i])) {
			if (stack.isStackEmpty())
				stack.push(str[i]);
			else {
				temp = stack.pop();
				priorityTemp = operationPriority(temp);
				prioriryStr = operationPriority(str[i]);

				if (priorityTemp < prioriryStr) {
					stack.push(temp);
					stack.push(str[i]);
				}
				else if (priorityTemp == prioriryStr) {
					strResult[iRes++] = temp;
					stack.push(str[i]);
				}
				else {
					bool check = stack.isStackEmpty();
					while (!isOpeningBracket(temp)) {
						strResult[iRes++] = temp;
						if (!stack.isStackEmpty())
							temp = stack.pop();
						else 
							temp = '(';
					}

					stack.push(str[i]);
				}
			}
		}

		else if (isClosingBracket(str[i])) {
			temp = stack.pop();

			while (!isOpeningBracket(temp))
			{

				strResult[iRes++] = temp;

				temp = stack.pop();
			}
		}

	}

	if (stack.isStackEmpty()) {
		strResult[iRes] = '\0';
		return;
	}

	while (!stack.isStackEmpty()) {
		temp = stack.pop();
		strResult[iRes++] = temp;
	}

	strResult[iRes] = '\0';

	return;
}

//Многоразрядные числа
int equationSolution(const char* str)
{
	int length = strlen(str);
	char* strRes = new char[length - numberOfBrackets(str, length) + 1];

	conversionToReversePolishEntry(str, strRes);

	length = strlen(str);
	Stack<int> stack;
	int temp1, temp2;

	for (int i = 0; i < length; i++)
	{
		if (isNumber(strRes[i]))
			stack.push(int(strRes[i] - '0'));
		else if (isOperation(strRes[i])) {
			temp2 = stack.pop();
			temp1 = stack.pop();
			stack.push(countingValue(temp1, temp2, strRes[i]));
		}
	}

	delete[] strRes;

	return stack.pop();
}