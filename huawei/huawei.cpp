#include "huawei.h"
#include "ui_huawei.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QTranslator>
#include <QSignalMapper>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QAction>
#include <QLocale>
#include "aescrypt.h"
#include "cfgfile.h"
#include "xmlfile.h"

HuaWei::HuaWei(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HuaWei)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    language = new QTranslator;
    g_language= new QTranslator;
    QSignalMapper *sign_mapper = new QSignalMapper(this);
    chinese = new QAction(tr("中文"), this);
    english = new QAction(tr("English"), this);
    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    about = new QAction(tr("About"), this);
    addAction(chinese);
    addAction(english);
    addAction(separator);
    addAction(about);
    sign_mapper->setMapping(chinese, 1);
    sign_mapper->setMapping(english, 2);
    sign_mapper->setMapping(about, 3);
    connect(chinese, SIGNAL(triggered(bool)), sign_mapper, SLOT(map()));
    connect(english, SIGNAL(triggered(bool)), sign_mapper, SLOT(map()));
    connect(about, SIGNAL(triggered(bool)), sign_mapper, SLOT(map()));
    connect(sign_mapper, SIGNAL(mapped(int)), this, SLOT(update_ui(int)));
    QLocale locale;
    if (locale.language() == QLocale::Chinese) update_ui(1);
}

void HuaWei::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QString path = event->mimeData()->urls()[0].toLocalFile();
        if (path.right(3) == "xml" || path.right(3) == "cfg")
            event->acceptProposedAction();
    } else if(event->mimeData()->hasHtml()) {
        event->acceptProposedAction();
    }
}

void HuaWei::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QString path = event->mimeData()->urls()[0].toLocalFile();
        if (path.right(3) == "xml") {
            ui->xml_line_edit_->setText(path);
        } else {
            ui->cfg_line_edit_->setText(path);
        }
    } else {
        ui->plain_line_edit_->setText(event->mimeData()->text());
    }
}

HuaWei::~HuaWei()
{
    delete ui;
}

void HuaWei::on_xml_tool_button__clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), NULL, tr("XML File(*.xml)"));
    if (file.isEmpty()) return ;
    ui->xml_line_edit_->setText(file);
}

void HuaWei::on_xml_en_button__clicked()
{
    QString file = ui->xml_line_edit_->text();
    if (file.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please specify the XML file."));
        return ;
    }
    QFileInfo file_info(file);
    if (!file_info.isFile()) {
        QMessageBox::warning(this, tr("Warning"), tr("The specified XML file does not exist."));
        return ;
    }
    XmlFile a(file);
    QString old_file = file;
    old_file.replace(file_info.absolutePath().size()+1, file_info.fileName().size(), "old_"+file_info.fileName());
    a.rename(old_file);
    if (!a.encrypt(file)) {
        a.rename(file);
        QMessageBox::critical(this, tr("Error"), tr("An unknown error."));
        return ;
    }
}

void HuaWei::on_xml_de_button__clicked()
{
    QString file = ui->xml_line_edit_->text();
    if (file.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please specify the XML file."));
        return ;
    }
    QFileInfo file_info(file);
    if (!file_info.isFile()) {
        QMessageBox::warning(this, tr("Warning"), tr("The specified XML file does not exist."));
        return ;
    }
    XmlFile a(file);
    if (!a.is_xml()) {
        QMessageBox::critical(this, tr("Error"), tr("The XML file has been damaged."));
        return ;
    }
    QString old_file = file;
    old_file.replace(file_info.absolutePath().size()+1, file_info.fileName().size(), "old_"+file_info.fileName());
    a.rename(old_file);
    if (!a.decrypt(file)) {
        a.rename(file);
        QMessageBox::critical(this, tr("Error"), tr("An unknown error."));
        return ;
    }
}
void HuaWei::on_cfg_tool_button__clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), NULL, tr("CFG File(*.cfg)"));
    if (file.isEmpty()) return ;
    ui->cfg_line_edit_->setText(file);
}

void HuaWei::on_cfg_en_button__clicked()
{
    QString file = ui->cfg_line_edit_->text();
    if (file.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please specify the CFG file."));
        return ;
    }
    QFileInfo file_info(file);
    if (!file_info.isFile()) {
        QMessageBox::warning(this, tr("Warning"), tr("The specified CFG file does not exist."));
        return ;
    }

    CfgFile a(file);
    QString old_file = file;
    old_file.replace(file_info.absolutePath().size()+1, file_info.fileName().size(), "old_"+file_info.fileName());
    a.rename(old_file);
    if (!a.encrypt(file)) {
        a.rename(file);
        QMessageBox::critical(this, tr("Error"), tr("An unknown error."));
        return ;
    }
}

void HuaWei::on_cfg_de_button__clicked()
{
    QString file = ui->cfg_line_edit_->text();
    if (file.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please specify the CFG file."));
        return ;
    }
    QFileInfo file_info(file);
    if (!file_info.isFile()) {
        QMessageBox::warning(this, tr("Warning"), tr("The specified CFG file does not exist."));
        return ;
    }
    CfgFile a(file);
    if (!a.is_cfg()) {
        QMessageBox::critical(this, tr("Error"), tr("The CFG file has been damaged."));
        return ;
    }
    QString old_file = file;
    old_file.replace(file_info.absolutePath().size()+1, file_info.fileName().size(), "old_"+file_info.fileName());
    a.rename(old_file);
    if (!a.decrypt(file)) {
        a.rename(file);
        QMessageBox::critical(this, tr("Error"), tr("An unknown error."));
        return ;
    }
}

void HuaWei::on_de_1_button__clicked()
{
    QString text = ui->plain_line_edit_->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("The ciphertext cannot be empty."));
        return ;
    }
    AesCrypt a(text, AesCrypt::$1);
    if (!a.check_format()) {
        QMessageBox::critical(this, tr("Warning"), tr("Error in the formatting of ciphertext."));
        return ;
    }
    text = a.decrypt();
    if (text == NULL) {
        QMessageBox::critical(this, tr("Error"), tr("Error in the formatting of ciphertext."));
        return ;
    }
    ui->plain_line_edit_->setText(text);
}

void HuaWei::on_de_2_button__clicked()
{
    QString text = ui->plain_line_edit_->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("The ciphertext cannot be empty."));
        return ;
    }
    AesCrypt a(text, AesCrypt::$2);
    if (!a.check_format()) {
        QMessageBox::critical(this, tr("Warning"), tr("Error in the formatting of ciphertext."));
        return ;
    }
    text = a.decrypt();
    if (text == NULL) {
        QMessageBox::critical(this, tr("Error"), tr("An unknown error."));
        return ;
    }
    ui->plain_line_edit_->setText(text);
}

void HuaWei::on_de_su_button__clicked()
{
    QString text = ui->plain_line_edit_->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("The ciphertext cannot be empty."));
        return ;
    }
    AesCrypt a(text, AesCrypt::SU);
    if (!a.check_format()) {
        QMessageBox::critical(this, tr("Warning"), tr("Error in the formatting of ciphertext."));
        return ;
    }
    text = a.decrypt();
    if (text == NULL) {
        QMessageBox::critical(this, tr("Error"), tr("An unknown error."));
        return ;
    }
    ui->plain_line_edit_->setText(text);
}

void HuaWei::update_ui(int i)
{
    if (i == 1) {
        language->load(":/language/chinese.qm");
        g_language->load(":/language/qt_zh_CN.qm");
        qApp->installTranslator(language);
        qApp->installTranslator(g_language);
        about->setText("关于");
        ui->retranslateUi(this);
    }else if (i == 2) {
        qApp->removeTranslator(language);
        qApp->removeTranslator(g_language);
        about->setText("About");
        ui->retranslateUi(this);
    }else if (i == 3) {
        QMessageBox::about(this, tr("About"), tr("Please don't used for illegal purposes\nBy:欲断魂\nVersion:1.2"));
    }
}
