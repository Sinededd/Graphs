#include "mathformconverter.h"
#include "qdebug.h"


QStringList MathFormConverter::InfixToPostfix(QStringList tokens)
{
    QStringList out;
    QStack<QString> operators;
    for(int i = 0; i < tokens.size(); i++)
    {
        if(tokens[i].size() > 1)
        {
            if(tokens[i] == "sin" || tokens[i] == "cos" || tokens[i] == "tg" || tokens[i] == "ctg")
            {
                while(!operators.isEmpty() && precedence[tokens[i]] <= precedence[operators.top()])
                {
                    out << operators.pop();
                }
                operators.push(tokens[i]);
            }
            else if(tokens[i][0].isDigit())
            {
                out << tokens[i];
            }
        }
        else
        {
            if(tokens[i][0].isLetterOrNumber())
            {
                out << tokens[i];
            }
            else if(tokens[i][0] == '(')
            {
                operators.push("(");
            }
            else if(tokens[i][0] == ')')
            {
                while(operators.top() != "(")
                {
                    out << operators.pop();
                }
                operators.pop();
            }
            else
            {
                if(tokens[i] == "-")
                {
                    if(i == 0 || tokens[i-1] == "(")
                    {
                        tokens[i] = "~";
                    }
                }
                while(!operators.isEmpty() && precedence[tokens[i]] <= precedence[operators.top()])
                {
                    out << operators.pop();
                }
                operators.push(tokens[i]);
            }
        }
    }
    while(!operators.isEmpty())
    {
        out << operators.pop();
    }
    qInfo() << out;
    return out;
}

QString MathFormConverter::StringFromTokens(QStringList tokens)
{
    QString out;
    for(int i = 0; i < tokens.size(); i++)
    {
        out += tokens[i];
    }
    return out;
}
