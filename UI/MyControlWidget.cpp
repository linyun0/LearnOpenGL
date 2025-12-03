#include "MyControlWidget.h"
#include "UI/DlgControl.h"
MyControlWidget::MyControlWidget(QWidget *parent,DialogCmd* control)
	:AppDialog(parent,control)
{
	ui.setupUi(this);
	
	m_NameToIdMap.insert({ "ModelIndexX" ,Model_Index_X});
	m_NameToIdMap.insert({ "ModelIndexY" ,Model_Index_Y});
	m_NameToIdMap.insert({ "ModelIndexZ" ,Model_Index_Z});
	m_NameToIdMap.insert({ "RoateXCheckBox" ,Model_Roate_X});
	m_NameToIdMap.insert({ "RoateYCheckBox" ,Model_Roate_Y});
	m_NameToIdMap.insert({ "RoateZCheckBox" ,Model_Roate_Z});
	m_NameToIdMap.insert({ "ModelScale" ,Model_Scale});
	m_NameToIdMap.insert({ "ModelLineModelCheckBox" ,Model_Line_Model});
	m_NameToIdMap.insert({ "ModelLineModelLabel" ,Model_Line_Val});
	m_NameToIdMap.insert({ "ModelPointModelCheckBox" ,Model_Point_Model});
	m_NameToIdMap.insert({ "ModelModPointelLabel" ,Model_Point_Val});
	m_NameToIdMap.insert({ "ModelMatrixSetPushButton" ,Model_Widget_PushButton });
	m_NameToIdMap.insert({ "ModelWidget" ,Model_Widget });

	m_NameToIdMap.insert({ "CameraIndexX" ,Camera_Position_X});
	m_NameToIdMap.insert({ "CameraIndexY" ,Camera_Position_Y});
	m_NameToIdMap.insert({ "CameraIndexZ" ,Camera_Position_Z});
	m_NameToIdMap.insert({ "CameraTargetX" ,Camera_Target_X});
	m_NameToIdMap.insert({ "CameraTargetY" ,Camera_Target_Y});
	m_NameToIdMap.insert({ "CameraTargetZ" ,Camera_Target_Z });
	m_NameToIdMap.insert({ "CameraRoateXCheckBox" ,Camera_Roate_X});
	m_NameToIdMap.insert({ "CameraRoateYCheckBox" ,Camera_Roate_Y});
	m_NameToIdMap.insert({ "CameraRoateZCheckBox" ,Camera_Roate_Z});
	m_NameToIdMap.insert({ "CameraPushButton" ,Camera_Widget_PushButton});
	m_NameToIdMap.insert({ "CameraWidget" ,Camera_Widget});

	m_NameToIdMap.insert({ "LightPositionX" , Light_Position_X });
	m_NameToIdMap.insert({ "LightPositionY" , Light_Position_Y });
	m_NameToIdMap.insert({ "LightPositionZ" , Light_Position_Z});	    
	m_NameToIdMap.insert({ "ColorPushButton" , Light_Color_PushButton }); 
	m_NameToIdMap.insert({ "AmbientCheckBox" , Light_Ambient_CheckBox});  
	m_NameToIdMap.insert({ "DiffuseCheckBox" , Light_Diffuse_CheckBox }); 
	m_NameToIdMap.insert({ "SpecularCheckBox" , Light_Specular_CheckBox });
	m_NameToIdMap.insert({ "SpecularIndex" , Light_Specular_Index	});
	m_NameToIdMap.insert({ "LightPushButton" , Light_Widget_PushButton });
	m_NameToIdMap.insert({ "LightWidget" , Light_Widget			});


	for (auto it : m_NameToIdMap) {
		m_IdToNameMap[it.second] = it.first;
	}
//	BuildConnection();
}

MyControlWidget::~MyControlWidget()
{}

//
//void MyControlWidget::OnPushButtonClicked()
//{
//
//}
//void MyControlWidget::OnCheckBoxStateChanged(int)
//{
//	Info info;
//	info.id = 10;
////	m_control->Active(info);
//}


//void MyControlWidget::BuildConnection()
//{
//	for (QWidget* child : this->findChildren<QWidget*>())
//	{
//		QString objectName = child->objectName();
//		if (objectName.contains("PushButton")) {
//			QPushButton* btn = (QPushButton*)child;
//			connect(btn, SIGNAL(clicked()), this, SLOT(OnPushButtonClicked()));
//		}
//		else if (objectName.contains("CheckBox")) {
//			QCheckBox* box = (QCheckBox*)(child);
//			connect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxStateChanged(int)));
//		}
//	}
//}
//
//void MyControlWidget::BreakConnection()
//{
//	for (QWidget* child : this->findChildren<QWidget*>())
//	{
//		QString objectName = child->objectName();
//		if (objectName.contains("PushButton")) {
//			QPushButton* btn = (QPushButton*)child;
//			disconnect(btn, SIGNAL(clicked()), this, SLOT(OnPushButtonClicked()));
//		}
//		else if (objectName.contains("CheckBox")) {
//			QCheckBox* box = (QCheckBox*)(child);
//			disconnect(box, SIGNAL(stateChanged(int)), this, SLOT(OnCheckBoxStateChanged(int)));
//		}
//	}
//}
