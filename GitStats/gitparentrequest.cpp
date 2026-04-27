#include "gitparentrequest.h"

#include <QProcess>
#include <QDebug>

#include <QRegularExpression>

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
