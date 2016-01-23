#ifndef STRINGPICKER_H
#define STRINGPICKER_H

#include <QWidget>

namespace Ui {
class StringPicker;
}

class StringPicker : public QWidget
{
    Q_OBJECT

public:
    explicit StringPicker(QString widgetName = "Picker",
                          QString label = "Pick your value",
                          QString buttonName = "Put",
                          QWidget *parent = 0);
    ~StringPicker();

signals:
    void OnValuePicked(QString *value);

private slots:
    void on_button_pickStr_clicked();

private:
    Ui::StringPicker *ui;
};

#endif // STRINGPICKER_H
