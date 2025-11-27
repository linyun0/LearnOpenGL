#include "SLWDColorDialog.h"
#pragma once


SLWDColorDialog::SLWDColorDialog(QWidget* parent):QWidget(parent)
{
    initWidget();
}

QColor SLWDColorDialog::GetColor()
{
    return m_currentColor;
}

void SLWDColorDialog::initWidget()
{
    m_hecagonColor = new HexagonGridWidget;
    m_frenshBtn = new QPushButton;
    m_closeBtn = new QPushButton;
    m_recoverBtn = new QPushButton;
    m_cameraBtn = new QPushButton;
    m_slider = new QSlider(Qt::Horizontal);
    m_percentage = new QLabel("0%");

    //QVBoxLayout* vLayout1 = new QVBoxLayout;
    //vLayout1->addWidget(m_hecagonColor);

    QHBoxLayout* hLayout1 = new QHBoxLayout;
    QLabel* sliderLabel = new QLabel("Transparency:");
    hLayout1->addWidget(sliderLabel);
    hLayout1->addWidget(m_slider);
    hLayout1->addWidget(m_percentage);

    int btnHeight = 30;

    //vLayout1->addLayout(hLayout1);

    QHBoxLayout* hLayout2 = new QHBoxLayout;
    m_frenshBtn->setFixedSize(btnHeight, btnHeight);
    hLayout2->addWidget(m_frenshBtn);
    m_closeBtn->setFixedSize(btnHeight * 3,btnHeight);
    hLayout2->addWidget(m_closeBtn);

    QVBoxLayout* vLayout1 = new QVBoxLayout;
    vLayout1->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    vLayout1->addLayout(hLayout2);
    QLabel* newBuild = new QLabel("Build");
    newBuild->setFixedHeight(0.8 * btnHeight);
    vLayout1->addWidget(newBuild);
    m_newColor = new QLabel;
    m_newColor->setFixedSize(btnHeight * 3, 2 * btnHeight);
    m_newColor->setStyleSheet("background-color:red;");
    m_newColor->setAutoFillBackground(true);
    vLayout1->addWidget(m_newColor);
    m_oldColor = new QLabel;
    m_oldColor->setFixedSize(btnHeight * 3, 2 * btnHeight);
    m_oldColor->setStyleSheet("background-color:blue;");
    m_oldColor->setAutoFillBackground(true);
    vLayout1->addWidget(m_oldColor);
    QLabel* currentLabel = new QLabel("Current Color");
    currentLabel->setFixedHeight(0.8 * btnHeight);
    vLayout1->addWidget(currentLabel);
    m_recoverBtn->setFixedSize(btnHeight * 3,btnHeight);
    vLayout1->addWidget(m_recoverBtn);
    m_cameraBtn->setFixedSize(1.5*btnHeight, 1.3*btnHeight);
    vLayout1->addWidget(m_cameraBtn);
    vLayout1->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QHBoxLayout* hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(m_hecagonColor);
    hLayout3->addLayout(vLayout1);

    QVBoxLayout* mainVLayout = new QVBoxLayout(this);
    mainVLayout->addLayout(hLayout3);
    mainVLayout->addLayout(hLayout1);

    connect(m_hecagonColor, SIGNAL(pickColor(QColor)), this, SLOT(ColorChange(QColor)));
    connect(m_slider, &QSlider::valueChanged, this, &SLWDColorDialog::SetPercentage);
}

void SLWDColorDialog::SetPercentage()
{
    int v = m_slider->value();
    int alpha = 255 - (v / 100.0) * 255.0;
    m_currentColor.setAlpha(alpha);

    m_percentage->setText( QString("%1").arg(v)+QString("%"));
    m_newColor->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4);").arg(m_currentColor.red()).arg(m_currentColor.green()).arg(m_currentColor.blue()).arg(m_currentColor.alpha()));
}

void  SLWDColorDialog::ColorChange(const QColor& newColor) {
    int r = newColor.red(); // 红色分量
    int g = newColor.green(); // 绿色分量
    int b = newColor.blue();   // 蓝色分量

    m_currentColor = newColor;
    m_newColor->setStyleSheet("background-color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");");
    emit ColorChanged(m_currentColor);
}
