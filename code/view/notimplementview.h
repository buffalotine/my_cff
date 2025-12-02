#ifndef NOTIMPLEMENTVIEW_H
#define NOTIMPLEMENTVIEW_H

#include <QWidget>

namespace Ui {
class NotImplementView;
}

class NotImplementView : public QWidget
{
    Q_OBJECT

public:
    explicit NotImplementView(QWidget *parent = nullptr);
    ~NotImplementView();

private:
    Ui::NotImplementView *ui;
};

#endif // NOTIMPLEMENTVIEW_H
