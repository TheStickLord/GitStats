#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(int Commits, QString Name, QString Email);

    int Commits = 0;
    int added = 0;
    int deleted = 0;
    QString Name = "";
    QString Email = "";

    bool operator<(const User& other) const {
        return Commits < other.Commits;
    }
};

#endif // USER_H
