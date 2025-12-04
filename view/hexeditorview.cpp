#include "hexeditorview.h"
#include "ui_hexeditorview.h"

HexEditorView::HexEditorView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HexEditorView)
{
    ui->setupUi(this);
}

HexEditorView::~HexEditorView()
{
    delete ui;
}
