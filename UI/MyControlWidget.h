#pragma once

#include <QWidget>
#include "ui_MyControlWidget.h"
#include "../MyGLDrawer.h"
class MyControlWidget : public AppDialog
{
	Q_OBJECT

public:
	MyControlWidget(QWidget *parent = nullptr, DialogCmd* control=nullptr);
	~MyControlWidget();
private:
	//void BuildConnection();
	//void BreakConnection();
//private slots:
//	virtual void OnPushButtonClicked();
//	virtual void OnCheckBoxStateChanged(int);
private:
	Ui::MyControlWidgetClass ui;
};

