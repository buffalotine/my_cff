#ifndef ADDRESSCONVERTERVIEW_H
#define ADDRESSCONVERTERVIEW_H

#include <QWidget>

namespace Ui {
class AddressConverterView;
}

class AddressConverterView : public QWidget
{
    Q_OBJECT

public:
    explicit AddressConverterView(QWidget *parent = nullptr);
    ~AddressConverterView();

public slots:
    void setConvertedAddress(const QString &va, const QString &rva, const QString &fo);

private slots:

    void on_lineEdit_va_textEdited(const QString &arg1);
    void on_lineEdit_rva_textEdited(const QString &arg1);
    void on_lineEdit_file_offset_textEdited(const QString &arg1);

signals:
    void reqAddressConvertByVa(const QString &arg1);
    void reqAddressConvertByRva(const QString &arg1);
    void reqAddressConvertByFo(const QString &arg1);


private:
    Ui::AddressConverterView *ui;

};

#endif // ADDRESSCONVERTERVIEW_H
