#include "mathchecker.h"

MathChecker::error_type MathChecker::lastError = MathChecker::None;

MathChecker::error_type MathChecker::GetLastError()
{
    return lastError;
}

void MathChecker::ThrowError(error_type throwType)
{
    lastError = throwType;
}

