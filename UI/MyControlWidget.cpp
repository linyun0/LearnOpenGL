#include "MyControlWidget.h"
MyControlWidget::MyControlWidget(QWidget *parent, MyGLDrawer* control)
	: QWidget(parent),m_control(control)
{
	ui.setupUi(this);

	BuildConnection();
}

MyControlWidget::~MyControlWidget()
{}


void MyControlWidget::OnPushButtonClicked()
{

}
void MyControlWidget::OnCheckBoxStateChanged(int)
{
	Info info;
	info.id = 10;
	m_control->Active(info);
}


void MyControlWidget::BuildConnection()
{
	for (QWidget* child : this->findChildren<QWidget*>())
	{
		QString objectName = child->objectName();
		if (objectName.contains("PushButton")) {
			QPushButton* btn = (QPushButton*)child;
			connect(btn, SIGNAL(clicked()), this, SLOT(OnPushButtonClicked()));
		}
		else if (objectName.contains("CheckBox")) {
			QCheckBox* box = (QCheckBox*)(child);
			connect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxStateChanged(int)));
		}
	}
}

void MyControlWidget::BreakConnection()
{
	for (QWidget* child : this->findChildren<QWidget*>())
	{
		QString objectName = child->objectName();
		if (objectName.contains("PushButton")) {
			QPushButton* btn = (QPushButton*)child;
			disconnect(btn, SIGNAL(clicked()), this, SLOT(OnPushButtonClicked()));
		}
		else if (objectName.contains("CheckBox")) {
			QCheckBox* box = (QCheckBox*)(child);
			disconnect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxStateChanged(int)));
		}
	}
}
