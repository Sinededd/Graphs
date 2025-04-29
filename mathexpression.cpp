#include "mathexpression.h"
#include "mathformconverter.h"
#include "mathparser.h"

MathExpression::MathExpression(QString exp) {
    inital = exp;
    postfixTok = MathFormConverter::InfixToPostfix(MathParser::CreateTokenList(exp));
}

qreal MathExpression::Calculate(qreal x)
{
    QStack<qreal> operandStack;
    for(int i = 0; i < postfixTok.size(); i++)
    {
        if(postfixTok[i].size() > 1)
        {
            if(postfixTok[i][0].isDigit())
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
                operandStack.push(x);
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
                default:
                    break;
                }
            }
        }
    }
    return operandStack.top();
}
