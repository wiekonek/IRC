#include "stringpicker.h"
#include "ui_stringpicker.h"

StringPicker::StringPicker(QString widgetName, QString label,
                           QString buttonName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringPicker)
{
    ui->setupUi(this);
    this->setWindowTitle(widgetName);
    ui->label_value->setText(label);
    ui->button_pickStr->setText(buttonName);
}

StringPicker::~StringPicker()
{
    delete ui;
}

void StringPicker::on_button_pickStr_clicked()
{
    QString *str = new QString(ui->lineEdit_value->text());
    emit OnValuePicked(str);
    this->close();
}
