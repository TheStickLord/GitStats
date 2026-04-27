#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(int Commits, QString Name, QString Email);

    int Commits = 0;
    int Added = 0;
    int Deleted = 0;
    QString Name = "";
    QString Email = "";

    bool operator<(const User& other) const {
        if (Commits == other.Commits) {
            return Added < other.Added;
        }
        return Commits < other.Commits;
    }
};

#endif // USER_H
