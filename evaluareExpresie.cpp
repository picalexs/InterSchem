//#include "functiiMatematice.h"
//#include "evaluareExpresie.h"
//#include "structs.h"
//
//int Prioritate(string c)  // prioritatea operatorilor
//{
//    int p;
//    if (c == "(" || c == ")")
//        p = 0;
//    else
//        if (c == "+" || c == "-")
//            p = 1;
//        else
//            if (c == "*" || c == "/")
//                p = 2;
//            else
//                if (c == "^")
//                    p = 3;
//                else
//                    if (c == "=" || c == "<" || c == ">")
//                        p = 4;
//                    else
//                        if (c == "cos" || c == "sin" || c == "ln" || c == "e" || c == "tg"|| c == "ctg" || c == "abs" || c == "sqrt")
//                            p = 5;
//                        else
//                            p = 6;
//    return p;
//}
//
//
//
//bool Operator(string op) {
//    if (op == "sin" || op == "cos" || op == "abs" || op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || op == "%")
//        return 1;
//    return 0;
//}
//
//int evaluare(functie E)
//{
//    int i, val;
//    for (i = 1; i <= 100; i++)
//    {
//        Opd[i] = 0;
//        Op[i] = "@";
//    }
//
//    top1 = 0;
//    top2 = 0;
//    for (i = 0; i < E.lung; i++)
//    {
//        if (strchr("0123456789", E[i]))
//        {
//            top1++;
//            val = E[i] - "/0";
//            Opd[top1] = val;
//        }
//
//    }
//}