#ifndef OPTIONALHEADERVIEW_H
#define OPTIONALHEADERVIEW_H

#include <QTableView>
#include <QSplitter>
#include <QMap>
#include <QStandardItemModel>


class OptionalHeaderView : public QTableView
{
    Q_OBJECT
private:
    QStandardItemModel* m_model = nullptr;

public:
    explicit OptionalHeaderView(QWidget *parent = nullptr);
    ~OptionalHeaderView();
    QWidget *parent;

    void onClickTableRow(const QModelIndex& index);


    // 获取指定行的数据
    QVariant getRowQVariant(int row)
    {
        if (row < 0 || row >= m_model->rowCount()) return 0;

        QStandardItem* idItem = m_model->item(row, 0);
        if (!idItem)
        {
            return 0;
        }

        QVariant var = idItem->data(Qt::UserRole);

        if (var.canConvert<QString>())
        {
            auto test = var.value<QString>();
            return var;
        }


        return 0;
    }


private:
    bool initTableHeader(int nColumn);

signals:
    void reqModifyValueField(const QString& offset, const QString& newValue);
    void reqUpdateData();

public slots:

    void addData(const QString& member, const QString& offset, const QString& size, const QString& value, const QString& meaning);

    void clearTable();

    void onItemChanged(QStandardItem *item);

private:

    void initConnect();

    // QWidget interface
public:
    void showEvent(QShowEvent *event) override;
};

#endif // OPTIONALHEADERVIEW_H
