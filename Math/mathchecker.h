#ifndef MATHCHECKER_H
#define MATHCHECKER_H

#include <QStringList>

class MathChecker
{

public:
    enum error_type {None, Invalid_Semantics, Invalid_Syntax, Invalid_Letter, Invalid_Brackets};

    static error_type GetLastError();
    static void ThrowError(error_type throwType);
    static void resetError();

    static bool CheckPostfixSyntax(const QStringList& postfixTok);
private:
    MathChecker() {}
    static error_type lastError;
};

#endif // MATHCHECKER_H
