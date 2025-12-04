#ifndef HEXEDITORVIEW_H
#define HEXEDITORVIEW_H

#include <QWidget>

namespace Ui {
class HexEditorView;
}

class HexEditorView : public QWidget
{
    Q_OBJECT

public:
    explicit HexEditorView(QWidget *parent = nullptr);
    ~HexEditorView();

private:
    Ui::HexEditorView *ui;
};

#endif // HEXEDITORVIEW_H
