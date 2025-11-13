#pragma once

#include <QWidget>
#include "ui_MyControlWidget.h"
#include "../MyGLDrawer.h"
class MyControlWidget : public QWidget
{
	Q_OBJECT

public:
	MyControlWidget(QWidget *parent = nullptr, MyGLDrawer* control=nullptr);
	~MyControlWidget();
private:
	void BuildConnection();
	void BreakConnection();
private slots:
	virtual void OnPushButtonClicked();
	virtual void OnCheckBoxStateChanged(int);
private:
	Ui::MyControlWidgetClass ui;
	MyGLDrawer* m_control= nullptr;
};

