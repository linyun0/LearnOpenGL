#include "DlgControl.h"
#include <qpushbutton.h>
#include <qcheckbox.h>


AppDialog::AppDialog(QWidget* parent, DialogCmd* cmd) :QWidget(parent), m_cmd(cmd)
{

}

void AppDialog::BuildConnection()
{
	for (QWidget* child : this->findChildren<QWidget*>())
	{
		QString objectName = child->metaObject()->className();
		if (objectName==QString("QPushButton")) {
			QPushButton* btn = (QPushButton*)child;
			connect(btn, &QPushButton::clicked, this,&AppDialog::OnPushButtonClicked);
		}
		else if (objectName==QString("QCheckBox")) {
			QCheckBox* box = (QCheckBox*)(child);
			connect(box, &QCheckBox::stateChanged, this, &AppDialog::OnCheckBoxStateChanged);
		}
		else if (objectName == QString("QLineEdit"))
		{
			QLineEdit* box = (QLineEdit*)(child);
			connect(box, &QLineEdit::textEdited, this, &AppDialog::OntextEdited);
		}
	}
}

void AppDialog::BreakConnection()
{
	for (QWidget* child : this->findChildren<QWidget*>())
	{
		QString objectName = child->metaObject()->className();
		if (objectName == QString("QPushButton")) {
			QPushButton* btn = (QPushButton*)child;
			disconnect(btn, &QPushButton::clicked, this, &AppDialog::OnPushButtonClicked);
		}
		else if (objectName == QString("QCheckBox")) {

			QCheckBox* box = (QCheckBox*)(child);
			disconnect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxStateChanged(int)));
		}
		else if (objectName == QString("QLineEdit"))
		{
			QLineEdit* box = (QLineEdit*)(child);
			disconnect(box, &QLineEdit::textEdited, this, &AppDialog::OntextEdited);
		}
	}
}

DlgControl* AppDialog::GetControl(int id)
{
	if (m_IdToNameMap.find(id) == m_IdToNameMap.end()) {
		return nullptr;
	};

	QString name = m_IdToNameMap[id];

	if (m_NameToControl.find(name) != m_NameToControl.end()) {
		return m_NameToControl[name];
	};

	if (CreateControl(name))
	{
		return m_NameToControl[name];
	};

	Q_ASSERT_X(false, "", ("No" + name + " Control").toLocal8Bit());
	return nullptr;
}

DlgControl* AppDialog::GetControl(QString name)
{
	if (m_NameToControl.find(name) != m_NameToControl.end()) {
		return m_NameToControl[name];
	};

	if (CreateControl(name))
	{
		return m_NameToControl[name];
	};

	return nullptr;
}

bool AppDialog::CreateControl(const QString& name)
{
	QWidget* childWidget = this->findChild<QWidget*>(name);
	bool ans = false;
	int  id = m_NameToIdMap[name];
	QString objectType = childWidget->metaObject()->className();
	if (objectType==QString("QPushButton")) {
		m_NameToControl[name] = (new PushButtonControl((QPushButton*)childWidget, id));
		ans = true;
	}
	else if (objectType==QString("CheckBox")) {
		m_NameToControl[name] = (new CheckBoxControl((QCheckBox*)childWidget, id));
		ans = true;
	}
	else if (objectType==QString("QWidget")) {
		m_NameToControl[name] = (new WidgetControl(childWidget, id));
		ans = true;
	}
	else if (objectType==QString("QPlainTextEdit")) {
		m_NameToControl[name] = (new PlainTextEditControl((QPlainTextEdit*)childWidget, id));
		ans = true;
	}
	else if (objectType == QString("QLabel")) {
		m_NameToControl[name] = (new LabelControl((QLabel*)childWidget, id));
		ans = true;
	}
	else if (objectType == QString("QLineEdit")) {
		m_NameToControl[name] = (new LineEditControl((QLineEdit*)childWidget, id));
		ans = true;
	}

	return ans;
}

void AppDialog::showEvent(QShowEvent* event)
{
	BuildConnection();

	QWidget::showEvent(event);
}

void AppDialog::OnCheckBoxStateChanged(int state)
{
	QString name = sender()->objectName();
	//	m_cmd->Activate(GetControl(name));
}
void AppDialog::OntextEdited(const QString& text)
{
	QString name = sender()->objectName();
	m_cmd->Activate(GetControl(name));
}
void AppDialog::OnPushButtonClicked()
{
	QString name = sender()->objectName();
	m_cmd->Activate(GetControl(name));
}

DialogCmd::DialogCmd()
{
}

DialogCmd::~DialogCmd()
{
	if (dlgBox) {
		delete dlgBox;
	}
}

void DialogCmd::SetDlgBox(AppDialog* dlg)
{
	dlgBox = dlg;
}

void DialogCmd::Activate(DlgControl* control)
{
}

void DialogCmd::init()
{
}

AppDialog* DialogCmd::GetDialog()
{
	if (dlgBox) {
		return dlgBox;
	}
}

DlgControl::DlgControl()
{
}

int DlgControl::GetId()
{
	return m_id;
}

bool DlgControl::isShow()
{
	return false;
}

QString DlgControl::GetString()
{
	return QString();
}

bool DlgControl::GetState()
{
	return false;
}

void DlgControl::Hide()
{
}

void DlgControl::Show()
{
}

void DlgControl::SetCheckState(bool state)
{
}

void DlgControl::SetString(const QString& str)
{
}

void DlgControl::SetFocus()
{
}

void DlgControl::SetColor(const QColor& color)
{
}

PushButtonControl::PushButtonControl(QPushButton* btn, int id) :m_obj(btn),m_id(id)
{
	m_id = id;
}

int PushButtonControl::GetId()
{
	return m_id;
}

void PushButtonControl::SetColor(const QColor& color)
{
	QString styleSheet = QString(
		"QPushButton {"
		"   background-color: %1;"
		"   border: none;"
		"}"
	).arg(color.name());
	m_obj->setText("");
	m_obj->setStyleSheet(styleSheet);
}

CheckBoxControl::CheckBoxControl(QCheckBox* checkBox, int id) :m_obj(checkBox), m_id(id)
{
	m_id = id;
}

bool CheckBoxControl::GetState()
{
	return m_obj->isChecked();
}

void CheckBoxControl::SetCheckState(bool state)
{
	m_obj->setCheckState(state ? Qt::Checked : Qt::Unchecked);
}

int CheckBoxControl::GetId()
{
	return m_id;
}

WidgetControl::WidgetControl(QWidget* widget, int id) :m_obj(widget)
{
}

bool WidgetControl::isShow()
{
	return m_obj->isVisible();
}

void WidgetControl::Hide()
{
	m_obj->hide();
}

void WidgetControl::Show()
{
	m_obj->show();
}

int WidgetControl::GetId()
{
	return m_id;
}

PlainTextEditControl::PlainTextEditControl(QPlainTextEdit* plainText, int id) :m_obj(plainText), m_id(id)
{
}

QString PlainTextEditControl::GetString()
{

	return m_obj->toPlainText();
}
int PlainTextEditControl::GetId()
{
	return m_id;
}
LabelControl::LabelControl(QLabel* plainText, int id) :m_obj(plainText)
{
}
void LabelControl::SetString(const QString& str)
{
	m_obj->setText(str);
}

int LabelControl::GetId()
{
	return m_id;
}

LineEditControl::LineEditControl(QLineEdit* lineEdit, int id):m_obj(lineEdit), m_id(id)
{

}

void LineEditControl::SetString(const QString& str)
{
	m_obj->setText(str);
}

QString LineEditControl::GetString()
{
	QString val("");
	val = m_obj->text();
	return val;
}

void LineEditControl::SetFocus()
{
	m_obj->setFocus();
}

int LineEditControl::GetId()
{
	return m_id;
}
