#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(int Commits, QString Name, QString Email);

    int Commits = 0;
    QString Name = "";
    QString Email = "";
};

#endif // USER_H
