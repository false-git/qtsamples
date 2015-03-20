#ifndef PERSONLISTMODEL_H
#define PERSONLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

class Person;

class PersonListModel : public QAbstractListModel
{
    Q_OBJECT
    // properties
    Q_PROPERTY(bool sortEnabled READ sortEnabled WRITE setSortEnabled NOTIFY sortEnabledChanged)
    Q_PROPERTY(int sortOrder READ sortOrder WRITE setSortOrder)
    Q_PROPERTY(QString sortRole READ sortRole WRITE setSortRole)
public:
    explicit PersonListModel(QObject *parent = 0);
    ~PersonListModel();

    enum PersonRole {
        NumberRole = Qt::UserRole + 1,
        NameRole,
        AgeRole
    };

    // UIから呼ばれる
    Q_INVOKABLE QVariant get(int row) const;

    // property accessor
    bool sortEnabled() const;
    int sortOrder() const;
    QString sortRole() const;

signals:
    // property change signal
    void sortEnabledChanged(bool arg);

public slots:
    // UIから呼ばれる
    void appendRow(int number, const QString &name, int age);
    void updateRow(int row, int number, const QString &name, int age);
    void removeRow(int row);
    // property accessor
    void setSortEnabled(bool arg);
    void setSortOrder(int arg);
    void setSortRole(QString arg);

private:
    // メンバ
    QList<Person *> m_list;
    bool m_sortEnabled;
    int m_sortOrder;
    QString m_sortRole;
    // private関数
    void sortRows();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // PERSONLISTMODEL_H
