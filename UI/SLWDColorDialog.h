#ifndef SLWDCOLORDIALOG
#define SLWDCOLORDOALOG
#define QT_NO_STDAFX
#include <QObject>
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlayout.h>
#include "HexagonGridWidget.h"

class SLWDColorDialog:public QWidget {

    Q_OBJECT
public:
    SLWDColorDialog(QWidget* parent);
public:
    QColor GetColor();

private:
    void initWidget();
signals:
    void ColorChanged(const QColor color);
private slots:
    void ColorChange(const QColor&);
    void SetPercentage();

private:
    HexagonGridWidget* m_hecagonColor;
    QPushButton* m_frenshBtn;
    QPushButton* m_closeBtn;
    QPushButton* m_recoverBtn;
    QPushButton* m_cameraBtn;
    QSlider* m_slider;
    QLabel* m_newColor ;
    QLabel* m_oldColor ;
    QLabel* m_percentage;

    QColor m_currentColor;
};




#endif // !SLWDCOLORDIALOG
