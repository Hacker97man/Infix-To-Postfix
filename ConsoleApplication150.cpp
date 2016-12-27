#include "stdafx.h"
#include<iostream>
#include<string>
#include<math.h>
using namespace std;
class Cstack {
private :
	int ptr;
	char arr[50];
public :
	Cstack() { ptr = -1; }
	bool isEmpty() { return ptr == -1 ? true : false; }
	char top() { if (!isEmpty()) arr[ptr]; else return -1; }
	void push(char N) { arr[++ptr] = N; }
	char pop() { return arr[ptr--]; }
	int size() { return ptr; }
};
class Fstack {
private:
	int ptr;
	float arr[50];
public:
	Fstack() { ptr = -1; }
	bool isEmpty() { return ptr == -1 ? true : false; }
	float top() { if (!isEmpty()) arr[ptr]; else return -1; }
	void push(float N) { arr[++ptr] = N; }
	float pop() { return arr[ptr--]; }
	int size() { return ptr; }

};
char Infix[50], Postfix[50];
bool isPop(char top, char symbol) {
	if (top == '(' || symbol == '(')
		return false;
	else if (symbol == ')')
		return true;
	else if (symbol == '^')
		return false;
	else if (top == '^')
		return true;
	else if (top == '*' || top == '/')
		return true;
	else if (symbol == '*' || symbol == '/')
		return false;
	return true;
}
void Convert() {
	Cstack OpS;
	int L = 0;
	for (int k = 0; k < strlen(Infix); k++)
		if (isdigit(Infix[k]))
			Postfix[L++] = Infix[k];
		else {
			while (!OpS.isEmpty() && isPop(OpS.top(), Infix[k]))
				Postfix[L++] = OpS.pop();
			if (OpS.top() == '(' && Infix[k] == ')')
				OpS.pop();
			else
				OpS.push(Infix[k]);
		}
		while (!OpS.isEmpty())
			Postfix[L++] = OpS.pop();
		Postfix[L] = '\0';

}

bool isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '/' || ch == '^' || ch == '*')
		return true;
	return false;
}
float PostfixEvals() {
	Fstack OpS;
	float op1, op2;
	for (int k = 0; k<strlen(Postfix); k++)
		if (isdigit(Postfix[k]))
			OpS.push(Postfix[k] - '0');
		else {
			op2 = OpS.pop();
			op1 = OpS.pop();
			switch (Postfix[k]) {
			case'+':OpS.push(op2 + op1); break;
			case'-':OpS.push(op1 - op2); break;
			case'*':OpS.push(op1*op2); break;
			case'/':op2 == 0 ? OpS.push(0) : OpS.push(op1 / op2); break;
			case'^':OpS.push(pow(op1, op2)); break;
			}
		}
		return
			OpS.pop();
}
int main()
{
	char Re;
	do {
		cout << "Enter Infix Expression(without spaces):\n\n";
		cin >> Infix;
		cout << endl;
		Convert();
		cout << "Equivalent postfix Expression :\n\n" << Postfix << endl << endl;
		cout.setf(ios::fixed);
		cout << PostfixEvals() << endl;
		cout << endl << "Do another try(y/n)?";
		cin >> Re;
		cout << endl;
		
	} while (Re == 'y'||Re=='Y');
    return 0;
}

