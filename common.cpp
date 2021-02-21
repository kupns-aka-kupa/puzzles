#include "common.hpp"

QString operator""_Q(const char *p, size_t)
{
    return QString(p);
}
