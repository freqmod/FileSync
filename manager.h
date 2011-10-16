#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QFileInfo>
namespace FileShare {
class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
protected:
    QList<QFileInfo> look_for_changed_files(const QString& topdir, const QString& subdir = "");
    void filesChanged(QList<QFileInfo>);
signals:
    //void filesChanged(QList<QFileInfo>);
public slots:
    void notifyDirectoryChanged(const QString& path);
};
}
#endif // MANAGER_H
