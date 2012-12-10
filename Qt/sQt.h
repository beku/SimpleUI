#ifndef SIMPLE_UI_QT_H
#define SIMPLE_UI_QT_H
#include "sQtCallbacks/sQt_Cb.h"
#include <QWidget>
#include <QPushButton>
#include "../sCallbackData/sCallbackData.h"

class SimpleUiQt : public QWidget
{
    Q_OBJECT
    
public:
    SimpleUiQt(struct sCbData *temp,QWidget *parent = 0);
    
private slots:
    void on_DoneButton_click();
    void on_QPushButton_click();
    void on_QComboBox_current_index_change(int index);
    void on_QComboBox_current_index_change( const QString & text );
    void on_QRadioButton_toggled(bool);
    void on_QCheckBox_toggled(bool);
    void on_QSlider_valueChanged(int);
private:
    struct sCbData *cb_data;
    QPushButton *ui_push_button;
    void FindReferencesAndUpdateData(char *name);
    void UpdateUI();
    void UpdateWidgetValue(char *type,char*value,char *name);
    void DisableDefaultAndConnectSignals();
};

#endif // SAMPLE1_H
