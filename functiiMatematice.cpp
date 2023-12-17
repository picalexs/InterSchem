#include "functiiMatematice.h"

bool esteSpatiu(const char& ch)
{
	return ch == ' ' || ch == '\r' || ch == '\n';
}

bool esteOperator(const char& ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '<' || ch == '>';
}
bool esteOperatorLung(const string& token)
{
	return token == "==" || token == "!=" || token == "<=" || token == ">=" || token == "&&" || token == "||";
}

bool esteFunctie(const string& token) {
	return token == "sin" || token == "cos" || token == "ln" || token == "tg" || token == "ctg" || token == "abs" || token == "sqrt";
}

bool esteCifra(const char& ch) {
	return ch >= '0' && ch <= '9';
}

bool esteNumar(const string& token)
{
	int nrPuncte = 0;
	if (token.empty())
		return false;
	if (token[0] != '-' && !esteCifra(token[0]))
		return false;
	for (int i = 1; i < token.size(); i++) {
		if (token[i] == '.') {
			nrPuncte++;
			if (nrPuncte > 1)
				return false;
		}
		else if (!esteCifra(token[i]))
			return false;
	}
	return true;
}