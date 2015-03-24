#include "personlistmodel.h"
#include <QHash>
#include <QMap>
#include <QDebug>
#include <algorithm>
#include <random>

// データホルダ

class Person {
public:
    int number;
    QString name;
    int age;
};

// コンストラクタ/デストラクタ

PersonListModel::PersonListModel(QObject *parent) : QAbstractListModel(parent), m_sortEnabled(false)
{
    const int max = 1000;
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution(1, max);
    for (int i = 0; i < max; i++) {
        Person *p = new Person;
        p->number = i + 1;
        p->name = QString("name%1").arg(max - i + 1);
        p->age = distribution(engine);
        m_list.append(p);
    }
}

PersonListModel::~PersonListModel()
{
    for (int i = 0; i < m_list.size(); i++) {
        delete m_list[i];
    }
    m_list.clear();
}

// 以下、UIから呼ばれるslot/INVOKABLEな関数群

QVariant PersonListModel::get(int row) const
{
    if (row < 0 || row >= m_list.size()) {
        return QVariant();
    }
    QMap<QString, QVariant> result;
    const QHash<int, QByteArray>& roles = roleNames();
    QHash<int, QByteArray>::const_iterator it;
    for (it = roles.begin(); it != roles.end(); it++) {
        result[it.value()] = data(index(row), it.key());
    }
    return result;
}

void PersonListModel::appendRow(int number, const QString &name, int age)
{
    Person *p = new Person;
    p->number = number;
    p->name = name;
    p->age = age;
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(p);
    endInsertRows();
    if (m_sortEnabled) {
        // 手抜き
        // 本来は、sort上の正しい位置を調べて、そこにinsertする方が
        // パフォーマンスが良い
        sortRows();
    }
}

void PersonListModel::updateRow(int row, int number, const QString &name, int age)
{
    if (row < 0 || row >= m_list.size()) {
        return;
    }
    Person *p = m_list[row];
    p->number = number;
    p->name = name;
    p->age = age;
    emit dataChanged(index(row), index(row));
}

void PersonListModel::removeRow(int row)
{
    if (row < 0 || row >= m_list.size()) {
        return;
    }
    beginRemoveRows(QModelIndex(), row, row);
    Person *p = m_list[row];
    m_list.removeAt(row);
    delete p;
    endRemoveRows();
}

// ソートを実現するprivate関数
void PersonListModel::sortRows()
{
    if (m_list.size() == 0) {
        return;
    }
    std::sort(m_list.begin(), m_list.end(), [&] (Person *left, Person *right) {
        bool result;
        if (m_sortOrder == Qt::AscendingOrder) {
            if (m_sortRole == "number") {
                result = left->number < right->number;
            } else if (m_sortRole == "name") {
                result = left->name < right->name;
            } else {
                result = left->age < right->age;
            }
        } else {
            if (m_sortRole == "number") {
                result = left->number > right->number;
            } else if (m_sortRole == "name") {
                result = left->name > right->name;
            } else {
                result = left->age > right->age;
            }
        }
        return result;
    });
    emit dataChanged(index(0), index(m_list.size() - 1));
}

// 以下、プロパティのaccessor

bool PersonListModel::sortEnabled() const
{
    return m_sortEnabled;
}

void PersonListModel::setSortEnabled(bool arg)
{
    if (m_sortEnabled == arg)
        return;

    m_sortEnabled = arg;
    emit sortEnabledChanged(arg);
    if (arg) {
        sortRows();
    }
}

int PersonListModel::sortOrder() const
{
    return m_sortOrder;
}

void PersonListModel::setSortOrder(int arg)
{
    m_sortOrder = arg;
    if (m_sortEnabled) {
        sortRows();
    }
}

QString PersonListModel::sortRole() const
{
    return m_sortRole;
}

void PersonListModel::setSortRole(QString arg)
{
    m_sortRole = arg;
    if (m_sortEnabled) {
        sortRows();
    }
}

// 以下、QAbstractListModelの関数のオーバーライド

int PersonListModel::rowCount(const QModelIndex &) const
{
    return m_list.size();
}

QVariant PersonListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.size()) {
        return QVariant();
    }
    Person *data = m_list[index.row()];
    switch (role) {
    case NumberRole:
        return data->number;
    case NameRole:
        return data->name;
    case AgeRole:
        return data->age;
    }
    return QVariant();
}

QHash<int, QByteArray> PersonListModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames;
    if (roleNames.size() == 0) {
        roleNames.insert(NumberRole, "number");
        roleNames.insert(NameRole, "name");
        roleNames.insert(AgeRole, "age");
    }
    return roleNames;
}

