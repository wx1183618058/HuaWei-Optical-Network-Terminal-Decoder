#ifndef HUAWEI_H
#define HUAWEI_H

#include <QWidget>

class QTranslator;
class QAction;

namespace Ui {
class HuaWei;
}

class HuaWei : public QWidget
{
    Q_OBJECT

public:
    explicit HuaWei(QWidget *parent = 0);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    ~HuaWei();

private slots:
    void on_xml_tool_button__clicked();
    void on_xml_en_button__clicked();
    void on_xml_de_button__clicked();
    void on_cfg_tool_button__clicked();
    void on_cfg_en_button__clicked();
    void on_cfg_de_button__clicked();
    void on_de_1_button__clicked();
    void on_de_2_button__clicked();
    void on_de_su_button__clicked();
    void update_ui(int i);

private:
    Ui::HuaWei *ui;
    QTranslator *language;
    QTranslator *g_language;
    QAction *chinese;
    QAction *english;
    QAction *about;
};

#endif // HUAWEI_H
