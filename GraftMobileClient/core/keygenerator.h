#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <QString>

class KeyGenerator
{
public:
    static QString generatePID();

    static QString generateSpendingKey();

    static QString generateViewKey();

    static QString generateUUID();
};

#endif // KEYGENERATOR_H
