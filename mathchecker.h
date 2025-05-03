#ifndef MATHCHECKER_H
#define MATHCHECKER_H

class MathChecker
{

public:
    enum error_type {None, Invalid_Syntax};
    // static bool IsExpressionValid(const QString& expression, bool isImplicit = false);
    // static bool IsExpressionValid(const QStringList& tokens, bool isImplicit = false);

    static error_type GetLastError();
    static void ThrowError(error_type throwType);

private:
    MathChecker() {}
    static error_type lastError;

    // static bool CheckSyntax(const QStringList& tokens);
    // static bool CheckSemantics(const QStringList& tokens, bool isImplicit);
    // static bool CheckBrackets(const QStringList& tokens);
    // static bool CheckOperators(const QStringList& tokens);
    // static bool CheckFunctions(const QStringList& tokens);
};

#endif // MATHCHECKER_H
