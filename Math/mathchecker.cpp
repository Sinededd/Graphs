#include "mathchecker.h"
#include "qdebug.h"
#include <QStack>

MathChecker::error_type MathChecker::lastError = MathChecker::None;

MathChecker::error_type MathChecker::GetLastError()
{
    return lastError;
}

void MathChecker::ThrowError(error_type throwType)
{
    lastError = throwType;
}

void MathChecker::resetError()
{
    lastError = None;
}

bool MathChecker::CheckPostfixSyntax(const QStringList &postfixTok)
{
    QStack<int> operandStack;
    for(int i = 0; i < postfixTok.size(); i++)
    {
        if(postfixTok[i].size() > 1)
        {
            if(postfixTok[i] == "sin" || postfixTok[i] == "cos" || postfixTok[i] == "tg" || postfixTok[i] == "ctg")
            {
                if(operandStack.size() == 0)
                {
                    MathChecker::ThrowError(MathChecker::Invalid_Syntax);
                    return 0;
                }
            }
            else if(postfixTok[i][0].isDigit())
            {
                operandStack.push(1);
            }
        }
        else
        {
            if(postfixTok[i][0].isNumber())
            {
                operandStack.push(1);
            }
            else if(postfixTok[i][0].isLetter())
            {
                if(postfixTok[i][0] == 'x')
                    operandStack.push(1);
                else if(postfixTok[i][0] == 'y')
                    operandStack.push(1);
                else
                {
                    MathChecker::ThrowError(Invalid_Letter);
                    return 0;
                }
            }
            else
            {
                QChar sym = postfixTok[i][0].unicode();
                if(sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^')
                {
                    if(operandStack.size() < 2)
                    {
                        MathChecker::ThrowError(Invalid_Syntax);
                        return 0;
                    }
                    else
                    {
                        operandStack.pop();
                    }
                }
                else if(sym == '~')
                {
                    if(operandStack.size() == 0)
                    {
                        MathChecker::ThrowError(MathChecker::Invalid_Syntax);
                        return 0;
                    }
                }
            }
        }
    }
    if(operandStack.size() > 1)
    {
        MathChecker::ThrowError(MathChecker::Invalid_Syntax);
        return 0;
    }
    return 1;
}

