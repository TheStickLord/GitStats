#include "gitparentrequest.h"

#include <QProcess>
#include <QDebug>

#include <QRegularExpression>
#include <unordered_map>

GitParentRequest::GitParentRequest() {}

void GitParentRequest::SetDirectory(QString dir)
{
    this->workingDir = dir;
}

QString GitParentRequest::GetStatus()
{
    QProcess process;

    process.setWorkingDirectory(workingDir);

    process.start("git", QStringList() << "status");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    return output;
}

std::vector<User> GitParentRequest::GetAuthors()
{
    QProcess process;
    process.setWorkingDirectory(workingDir);

    // It is often better to use a list of arguments to avoid shell injection/parsing issues
    process.start("git", QStringList() << "shortlog" << "-sne" << "HEAD");

    if (!process.waitForFinished()) {
        return {}; // Handle error: git not found or crashed
    }

    // Read output and split into individual lines
    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    std::vector<User> users;

    // Pattern: capture count, name, and email
    // Example line: "   145  Jane Doe <jane@example.com>"
    QRegularExpression re(R"(\s*(\d+)\t(.+)\s+<(.+)>)");

    for (const QString& line : std::as_const(lines))
    {
        QRegularExpressionMatch match = re.match(line);

        if (match.hasMatch())
        {
            int commits = match.captured(1).toInt();
            QString authorName = match.captured(2).trimmed();
            QString email = match.captured(3).trimmed();

            users.push_back(User(commits, authorName, email));
        }
    }

    return users;
}

std::vector<User> GitParentRequest::GetAuthorsFile(QString file)
{
    QProcess process;
    process.setWorkingDirectory(workingDir);

    process.start("git", QStringList()
                             << "shortlog"
                             << "-sne"
                             << "HEAD"
                             << "--"
                             << file);

    if (!process.waitForFinished())
        return {};

    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    std::vector<User> users;

    QRegularExpression re(R"(^\s*(\d+)\s+(.+?)\s+<(.+)>$)");

    for (const QString& line : std::as_const(lines))
    {
        QRegularExpressionMatch match = re.match(line);

        if (match.hasMatch())
        {
            int commits = match.captured(1).toInt();
            QString authorName = match.captured(2).trimmed();
            QString email = match.captured(3).trimmed();

            users.push_back(User(commits, authorName, email));
        }
    }

    return users;
}

std::vector<User> GitParentRequest::GetDiffByUser()
{
    QProcess process;
    qDebug() << workingDir;
    process.setWorkingDirectory(workingDir);

    process.start("git", QStringList()
                             << "log"
                             << "--format=author:%an"
                             << "--numstat"
                             << "HEAD");

    if (!process.waitForFinished())
        return {};

    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    std::vector<User> users;
    QString currentAuthor;

    QRegularExpression authorRe(R"(^author:(.+)$)");
    QRegularExpression numstatRe(R"(^(\d+)\s+(\d+)\s+(.+)$)");

    for (const QString& line : lines)
    {
        auto authorMatch = authorRe.match(line);

        if (authorMatch.hasMatch())
        {
            currentAuthor = authorMatch.captured(1).trimmed();

            bool found = false;
            for (const User& user : users)
            {
                if (user.Name == currentAuthor)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                User u;
                u.Name = currentAuthor;
                users.push_back(u);
            }

            continue;
        }

        auto statMatch = numstatRe.match(line);

        if (statMatch.hasMatch() && !currentAuthor.isEmpty())
        {
            int added = statMatch.captured(1).toInt();
            int deleted = statMatch.captured(2).toInt();

            for (User& user : users)
            {
                if (user.Name == currentAuthor)
                {
                    user.Added += added;
                    user.Deleted += deleted;
                    break;
                }
            }
        }
    }

    return users;
}

std::vector<User> GitParentRequest::GetDiffByUserFile(QString file)
{
    QProcess process;
    process.setWorkingDirectory(workingDir);

    process.start("git", QStringList()
                             << "log"
                             << "--format=author:%an <%ae>"
                             << "--numstat"
                             << "HEAD"
                             << "--"
                             << file);

    if (!process.waitForFinished())
        return {};

    QString output = QString::fromUtf8(process.readAllStandardOutput());
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    std::unordered_map<QString, User> totals;
    QString currentKey;

    QRegularExpression authorRe(R"(^author:(.+)\s+<(.+)>$)");
    QRegularExpression numstatRe(R"(^(\d+)\s+(\d+)\s+(.+)$)");

    for (const QString& line : std::as_const(lines))
    {
        auto authorMatch = authorRe.match(line);

        if (authorMatch.hasMatch())
        {
            QString name = authorMatch.captured(1).trimmed();
            QString email = authorMatch.captured(2).trimmed();

            currentKey = email;

            if (!totals.contains(currentKey))
                totals[currentKey] = User(0, name, email);

            continue;
        }

        auto statMatch = numstatRe.match(line);

        if (statMatch.hasMatch() && !currentKey.isEmpty())
        {
            int added = statMatch.captured(1).toInt();
            int deleted = statMatch.captured(2).toInt();

            totals[currentKey].Added += added;
            totals[currentKey].Deleted += deleted;
        }
    }


    std::vector<User> users;

    for (const auto& pair : totals)
        users.push_back(pair.second);

    return users;
}

QString GitParentRequest::PullRepo()
{
    QProcess process;
    process.setWorkingDirectory(workingDir);

    process.start("git", QStringList() << "pull");
    process.waitForFinished();

    QString output =
        QString::fromUtf8(process.readAllStandardOutput());

    QString errors =
        QString::fromUtf8(process.readAllStandardError());

    return output + errors;
}

QStringList GitParentRequest::GetFiles()
{
    QDir dir(workingDir);

    QStringList files = dir.entryList(
        QDir::Files | QDir::NoDotAndDotDot
        );

    return files;
}

QString GitParentRequest::GetRepoName()
{
    QProcess process;
    process.setWorkingDirectory(workingDir);

    process.start("git", QStringList()
                             << "remote"
                             << "get-url"
                             << "origin");

    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    return output;
}
