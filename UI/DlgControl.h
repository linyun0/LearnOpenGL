#ifndef DLGCONTROL_H
#define DLGCONTROL_H
#include <qwidget.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <unordered_map>
#include <qplaintextedit.h>
#include <qlabel.h>
#include <QLineEdit>
#define Model_Index_X 0
#define Model_Index_Y 1
#define Model_Index_Z 2
#define Model_Roate_X 3
#define Model_Roate_Y 4
#define Model_Roate_Z 5
#define Model_Scale	  6
#define Model_Line_Model 7
#define Model_Line_Val 8
#define Model_Point_Model 9
#define Model_Point_Val 10
#define Model_Widget_PushButton 11
#define Model_Widget 12

#define Camera_Position_X Model_Widget+1
#define Camera_Position_Y Model_Widget+2
#define Camera_Position_Z Model_Widget+3
#define Camera_Target_X	  Model_Widget+4
#define Camera_Target_Y	Model_Widget+5
#define Camera_Target_Z Model_Widget+6
#define Camera_Roate_X Model_Widget+7
#define Camera_Roate_Y Model_Widget+8
#define Camera_Roate_Z Model_Widget+9
#define Camera_Widget_PushButton Model_Widget+10
#define Camera_Widget Model_Widget+11

#define Light_Position_X	    Camera_Widget+1
#define Light_Position_Y	    Camera_Widget+2
#define Light_Position_Z	    Camera_Widget+3
#define Light_Color_PushButton  Camera_Widget+4
#define Light_Ambient_CheckBox  Camera_Widget+5
#define Light_Diffuse_CheckBox  Camera_Widget+6
#define Light_Specular_CheckBox Camera_Widget+7
#define Light_Specular_Index	Camera_Widget+8
#define Light_Widget_PushButton Camera_Widget+9
#define Light_Widget			Camera_Widget+10
#define Light_Rotate			Camera_Widget+11



class AppDialog;

class DlgControl {
public:
	DlgControl();
public:
	virtual int GetId();
	virtual bool isShow();
	virtual QString GetString();
	virtual bool GetState();

	virtual void Hide();
	virtual void Show();
	virtual void SetCheckState(bool state);
	virtual void SetString(const QString& str);
	virtual void SetFocus();
	virtual void SetColor(const QColor& color);
protected:
	int m_id;
};

class PushButtonControl :public DlgControl
{
public:
	PushButtonControl(QPushButton* btn, int id);
	virtual int GetId();
	virtual void SetColor(const QColor& color) override;
private:
	QPushButton* m_obj;
	int m_id;
};

class CheckBoxControl :public DlgControl {
public:
	CheckBoxControl(QCheckBox* checkBox, int id);
	virtual bool GetState() override;
	virtual void SetCheckState(bool state) override;
	virtual int GetId();
private:
	QCheckBox* m_obj;
	int m_id;
};

class LineEditControl :public DlgControl {
public:
	LineEditControl(QLineEdit* lineEdit, int id);
	virtual void SetString(const QString& str);
	virtual QString GetString();
	virtual void SetFocus();
	virtual int GetId();

private:
	QLineEdit* m_obj;
	int m_id;
};

class PlainTextEditControl :public DlgControl {

public:
	PlainTextEditControl(QPlainTextEdit* checkBox, int id);
	virtual QString GetString() override;
	virtual int GetId();
private:
	QPlainTextEdit* m_obj;
	int m_id;
};

class LabelControl :public DlgControl {

public:
	LabelControl(QLabel* checkBox, int id);
	virtual void SetString(const QString& str) override;
	virtual int GetId();
private:
	QLabel* m_obj;
	int m_id;
};

class WidgetControl :public DlgControl {
public:
	WidgetControl(QWidget* widget, int id);
	bool isShow() override;
	virtual void Hide() override;
	virtual void Show() override;
	virtual int GetId();
private:
	QWidget* m_obj;
	int m_id;
};

class DialogCmd {
public:
	DialogCmd();
	~DialogCmd();
protected:
	AppDialog* dlgBox = nullptr;
public:
	void SetDlgBox(AppDialog* dlg);
	virtual void Activate(DlgControl* control);
	virtual void init();
    virtual void InitUI();
	AppDialog* GetDialog();
};

class AppDialog :public QWidget {
	
public:
	AppDialog(QWidget* parent, DialogCmd* cmd=nullptr);
private:
	void BuildConnection();
	void BreakConnection();
public:
	DlgControl* GetControl(int id);
	DlgControl* GetControl(QString name);
protected:
	std::unordered_map<QString, int> m_NameToIdMap;
	std::unordered_map<int, QString> m_IdToNameMap;
private:
	std::unordered_map<QString, DlgControl*> m_NameToControl;
	bool CreateControl(const QString& name);
	DialogCmd* m_cmd;
	virtual void showEvent(QShowEvent* event) override;
private slots:
	virtual void OnPushButtonClicked();
	virtual void OnCheckBoxStateChanged(int state);
	virtual void OntextEdited(const QString& text);
};






#endif 