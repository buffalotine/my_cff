#include "addressconverterview.h"
#include "ui_addressconverterview.h"
#include "utils/logger.h"

AddressConverterView::AddressConverterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddressConverterView)
{
    ui->setupUi(this);

    ui->addr_con_splitter->setSizes({100, 800});

}

AddressConverterView::~AddressConverterView()
{
    delete ui;
}

void AddressConverterView::setConvertedAddress(const QString &va, const QString &rva, const QString &fo)
{
    ui->lineEdit_va->setText(va);
    ui->lineEdit_rva->setText(rva);
    ui->lineEdit_file_offset->setText(fo);
}

void AddressConverterView::on_lineEdit_va_textEdited(const QString &arg1)
{
    LOG_DEBUG(__FUNCTION__" arg1: %s", arg1.toUtf8().constData());
    emit reqAddressConvertByVa(arg1);
}


void AddressConverterView::on_lineEdit_rva_textEdited(const QString &arg1)
{
    LOG_DEBUG(__FUNCTION__" arg1: %s", arg1.toUtf8().constData());
    emit reqAddressConvertByRva(arg1);

}


void AddressConverterView::on_lineEdit_file_offset_textEdited(const QString &arg1)
{
    LOG_DEBUG(__FUNCTION__" arg1: %s", arg1.toUtf8().constData());
    emit reqAddressConvertByFo(arg1);

}
