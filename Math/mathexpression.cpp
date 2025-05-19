#include "mathexpression.h"
#include "mathformconverter.h"

MathExpression::MathExpression(QString exp) {
    inital = exp;
    postfixTok = MathFormConverter::InfixToPostfix(MathParser::CreateTokenList(exp));
    qInfo() << MathChecker::GetLastError();
    if(MathChecker::GetLastError() != MathChecker::None)
    {
        isValidExp = 0;
        errorType = MathChecker::GetLastError();
    }
    else
    {
        isValidExp = 1;
        errorType = MathChecker::None;
    }
}

qreal MathExpression::Calculate(const qreal &x, const qreal &y)
{
    if(isImplicit() && y == INFINITY)
    {
        throw std::invalid_argument("not enough parameters for calculation implicit function");
    }
    QStack<qreal> operandStack;
    for(int i = 0; i < postfixTok.size(); i++)
    {
        if(postfixTok[i].size() > 1)
        {
            if(postfixTok[i] == "sin")
            {
                operandStack.push(qSin(operandStack.pop()));
            }
            else if(postfixTok[i] == "cos")
            {
                operandStack.push(qCos(operandStack.pop()));
            }
            else if(postfixTok[i] == "tg")
            {
                operandStack.push(qTan(operandStack.pop()));
            }
            else if(postfixTok[i] == "ctg")
            {
                operandStack.push(1 / qTan(operandStack.pop()));
            }
            else if(postfixTok[i][0].isDigit())
            {
                operandStack.push(postfixTok[i].toDouble());
            }
        }
        else
        {
            if(postfixTok[i][0].isNumber())
            {
                operandStack.push(postfixTok[i].toDouble());
            }
            else if(postfixTok[i][0].isLetter())
            {
                if(postfixTok[i][0] == 'x')
                    operandStack.push(x);
                else if(postfixTok[i][0] == 'y')
                    operandStack.push(y);
            }
            else
            {
                qreal buf;
                switch (postfixTok[i][0].unicode()) {
                case '+':
                    operandStack.push(operandStack.pop() + operandStack.pop());
                    break;
                case '-':
                    buf = operandStack.pop();
                    operandStack.push(operandStack.pop() - buf);
                    break;
                case '*':
                    operandStack.push(operandStack.pop() * operandStack.pop());
                    break;
                case '/':
                    buf = operandStack.pop();
                    operandStack.push(operandStack.pop() / buf);
                    break;
                case '^':
                    buf = operandStack.pop();
                    operandStack.push(qPow(operandStack.pop(), buf));
                    break;
                case '~':
                    operandStack.push(-operandStack.pop());
                    break;
                default:
                    break;
                }
            }
        }
    }
    return operandStack.top();
}

bool MathExpression::isImplicit()
{
    return postfixTok.contains("y");
}
