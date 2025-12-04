#ifndef SECTIONHEADERVIEW_H
#define SECTIONHEADERVIEW_H

#include <QWidget>

namespace Ui {
class SectionHeaderView;
}

class SectionHeaderView : public QWidget
{
    Q_OBJECT

public:
    explicit SectionHeaderView(QWidget *parent = nullptr);
    ~SectionHeaderView();

private:
    Ui::SectionHeaderView *ui;
};

#endif // SECTIONHEADERVIEW_H
