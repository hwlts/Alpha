#include "TravelManipulator.h"

//���캯��
TravelManipulator::TravelManipulator() : 
	m_fMoveSpeed(1.0f),
	m_bLeftButtonDown(false),
	m_fpushX(0),
	m_fpushY(0),
	m_fAngle(2.5),
	m_bPeng(true)
{
	m_vPosition = osg::Vec3(-22.0f,-274.0f,100.0f);
	m_vRotation = osg::Vec3(osg::PI_2,0.0f,0.0f);
}

//��������
TravelManipulator::~TravelManipulator()
{}

//�����μ��뵽����֮��
TravelManipulator* TravelManipulator::TravelToScene(osg::ref_ptr<osgViewer::Viewer> viewer)
{
	TravelManipulator* camera = new TravelManipulator();

	viewer->setCameraManipulator(camera);

	camera->m_pHostViewer = viewer;

	return camera;
}

//���þ���
void TravelManipulator::setByMatrix(const osg::Matrixd& matrix)
{}

//���������
void TravelManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{}

//�õ�����
osg::Matrixd TravelManipulator::getMatrix() const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0],osg::Vec3(1.0f,0.0f,0.0f),
						   m_vRotation._v[1],osg::Vec3(0.0f,1.0f,0.0f),
						   m_vRotation._v[2],osg::Vec3(0.0f,0.0f,1.0f));

	return mat*osg::Matrixd::translate(m_vPosition);
}

//�õ������
osg::Matrix TravelManipulator::getInverseMatrix() const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0],osg::Vec3(1.0f,0.0f,0.0f),
		m_vRotation._v[1],osg::Vec3(0.0f,1.0f,0.0f),
		m_vRotation._v[2],osg::Vec3(0.0f,0.0f,1.0f));

	return osg::Matrixd::inverse(mat*osg::Matrixd::translate(m_vPosition));
}

//�¼�������
bool TravelManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
{
	//�õ�����λ��
	float mouseX = ea.getX();
	float mouseY = ea.getY();

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			//�ո��
			if(ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)
			{
				us.requestRedraw();
				us.requestContinuousUpdate();
				return true;
			}
			//���ƶ�
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
			{
				ChangePosition(osg::Vec3(0,0,m_fMoveSpeed));
				return true;
			}
			//���ƶ�
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Up)
			{
				ChangePosition(osg::Vec3(0,0,-m_fMoveSpeed));
				return true;
			}
			//�����ٶ�
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Left)
			{
				m_fMoveSpeed += 1.0f;
				return true;
			}
			//�����ٶ�
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Right)
			{
				m_fMoveSpeed += 1.0f;
				return true;
			}
			//ǰ��
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_W)
			{
				ChangePosition(osg::Vec3(0,m_fMoveSpeed*sinf(osg::PI_2+m_vRotation._v[2]),0));

				ChangePosition(osg::Vec3(m_fMoveSpeed*cosf(osg::PI_2+m_vRotation._v[2]),0,0));

				return true;
			}
			//����
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_S)
			{
				ChangePosition(osg::Vec3(0,-m_fMoveSpeed*sinf(osg::PI_2+m_vRotation._v[2]),0));

				ChangePosition(osg::Vec3(-m_fMoveSpeed*cosf(osg::PI_2+m_vRotation._v[2]),0,0));

				return true;
			}
			//����
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_A)
			{
				ChangePosition(osg::Vec3(0,m_fMoveSpeed*cosf(osg::PI_2+m_vRotation._v[2]),0));

				ChangePosition(osg::Vec3(-m_fMoveSpeed*sinf(osg::PI_2+m_vRotation._v[2]),0,0));

				return true;
			}
			//����
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_D)
			{
				ChangePosition(osg::Vec3(0,-m_fMoveSpeed*cosf(osg::PI_2+m_vRotation._v[2]),0));

				ChangePosition(osg::Vec3(m_fMoveSpeed*sinf(osg::PI_2+m_vRotation._v[2]),0,0));

				return true;
			}
			//Right
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_C)
			{
				m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
			}
			//Left
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Z)
			{
				m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
			}
			//�ı�����
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_E)
			{
				m_fAngle -= 0.2;
				return true;
			}
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Q)
			{
				m_fAngle += 0.2;
				return true;
			}
			return false;
		}
	//��갴��
	case(osgGA::GUIEventAdapter::PUSH) :
		if (ea.getButton() == 1)
		{
			m_fpushX = mouseX;
			m_fpushY = mouseY;
			
			m_bLeftButtonDown = true;
		}
		return false;
	//�϶�
	case(osgGA::GUIEventAdapter::DRAG) :
		if (m_bLeftButtonDown)
		{
			m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle*(mouseX-m_fpushX));

			m_vRotation._v[0] += osg::DegreesToRadians(1.1*(mouseY-m_fpushY));

			if (m_vRotation._v[0] >= 3.14)
			{
				m_vRotation._v[0] = 3.14;
			}

			if (m_vRotation._v[0] <= 0)
			{
				m_vRotation._v[0] = 0;
			}
		}
		return false;
	//����ͷ�
	case(osgGA::GUIEventAdapter::RELEASE) :
		if (ea.getButton() == 1)
		{
			m_bLeftButtonDown = false;
		}
		return false;
	default:
		return false;
	}
}

//λ�ñ任����
void TravelManipulator::ChangePosition(osg::Vec3& delta)
{
	//��ײ���
	if (m_bPeng)
	{
		//�õ���λ��
		osg::Vec3 newPos1 = m_vPosition = delta;

		osgUtil::IntersectVisitor ivXY;

		//�����µ�λ�õõ������߶μ��
		osg::ref_ptr<osg::LineSegment> lineXY = new osg::LineSegment(newPos1,m_vPosition);

		osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(newPos1+osg::Vec3(0.0f,0.0f,10.0f),newPos1-osg::Vec3(0.0f,0.0f,-10.0f));

		ivXY.addLineSegment(lineZ.get());

		ivXY.addLineSegment(lineXY.get());

		//�ṹ�������
		m_pHostViewer->getSceneData()->accept(ivXY);
		
		//���û����ײ���
		if (!ivXY.hits())
		{
			m_vPosition += delta;
		}
	}
	else
	{
		m_vPosition += delta;
	}
}

//�����ٶ�
void TravelManipulator::setSpeed(float& sp)
{
	m_fMoveSpeed = sp;
}

//�õ���ǰ�ٶ�
float TravelManipulator::getSpeed()
{
	return m_fMoveSpeed;
}

//������ʼλ��
void TravelManipulator::setPosition(osg::Vec3& position)
{
	m_vPosition = position;
}

//�õ���ǰλ��
osg::Vec3  TravelManipulator::getPosition()
{
	return m_vPosition;
}