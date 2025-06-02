#include "mathparser.h"
#include "mathchecker.h"


QStringList MathParser::CreateTokenList(QString exp, int &funcType)
{
    exp = exp.simplified().replace(" ", "");
    //Проверка правой и левой части
    QStringList parts = exp.split("=");
    if(parts.size() == 1)
    {
        if(parts[0].contains('y'))
        {
            MathChecker::ThrowError(MathChecker::Invalid_Syntax);
            return QStringList();
        }
        else if(parts[0].contains('x'))
        {
            funcType = 1;
        }
    }
    else if(parts.size() == 2)
    {
        if(parts[0] == "y" && !parts[1].contains('y'))
        {
            exp.erase(exp.cbegin(), exp.cbegin() + 2);
            funcType = 1;
        }
        else if(parts[1] == "y" && !parts[0].contains('y'))
        {
            exp.erase(exp.cend() - 2, exp.cend());
            funcType = 1;
        }
        else if( parts[0] == "x" && !parts[1].contains('x'))
        {
            exp.erase(exp.cbegin(), exp.cbegin() + 2);
            for(int i = 0; i < exp.size(); i++)
            {
                if(exp[i] == 'y')
                    exp[i] = 'x';
            }
            funcType = 2;
        }
        else if (parts[1] == "x"  && !parts[0].contains('x')) {
            exp.erase(exp.cend() - 2, exp.cend());
            for(int i = 0; i < exp.size(); i++)
            {
                if(exp[i] == 'y')
                    exp[i] = 'x';
            }
            funcType = 2;
        }
        else
        {
            funcType = 0;
        }
    }
    else
    {
        MathChecker::ThrowError(MathChecker::Invalid_Syntax);
        return QStringList();
    }



    QStringList tokens;
    QString cleaned = exp.simplified().replace(" ", "");
    QString tokenStr;

    //Парсинг строки
    QRegularExpressionMatchIterator it = re.globalMatch(cleaned);

    QString prevToken;
    bool ok;
    bool isEqual = 0;
    while (it.hasNext()) {
        QString token = it.next().captured(1);
        if (!token.isEmpty())
        {
            prevToken.toDouble(&ok);
            if((ok && token.size() == 1 && token[0].isLetter()) || (ok && token == "(") ||
                (prevToken.size() == 1 && prevToken[0].isLetter() && token == "(") || (prevToken == ")" && token == "("))
            {
                tokens << "*";
                tokenStr += "*";
            }
            if(token == "=")
            {
                tokens << "-";
                tokenStr += "-";
                tokens << "(";
                tokenStr += "(";
                isEqual = 1;
            }
            else
            {
                tokens << token;
                tokenStr += token;
            }
        }

        prevToken = token;
    }
    if(isEqual)
    {
        tokens << ")";
        tokenStr += ")";
    }
    QString out1 = tokenStr;
    QString out2 = cleaned;
    out1.remove("*").remove("(").remove(")").remove("-").remove("=");
    out2.remove("*").remove("(").remove(")").remove("-").remove("=");
    if(out1 != out2)
    {
        MathChecker::ThrowError(MathChecker::Invalid_Semantics);
    }
    return tokens;
}
