#include "SimpleTraveller.h"

SimpleTraveller::SimpleTraveller() :
	m_vPosition(osg::Vec3(0.0f,0.0f,5.0f)),
	m_vRotation(osg::Vec3(osg::PI_2,0.0f,0.0f)),
	m_iStep(1.0f),
	m_fRotateStep(0.01),
	m_bLeftDown(false) {}

SimpleTraveller::~SimpleTraveller()
{}

void SimpleTraveller::setByMatrix(const osg::Matrixd& matrix)
{}

void SimpleTraveller::setByInverseMatrix(const osg::Matrixd& matrix)
{}

osg::Matrixd SimpleTraveller::getMatrix() const
{
	osg::Matrixd mat;

	mat.makeTranslate(m_vPosition);

	return osg::Matrixd::rotate(m_vRotation[0],osg::X_AXIS,m_vRotation[1],osg::Y_AXIS,m_vRotation[2],osg::Z_AXIS)*mat;
}

osg::Matrixd SimpleTraveller::getInverseMatrix() const
{
	osg::Matrixd mat;

	mat.makeTranslate(m_vPosition);

	return osg::Matrixd::inverse(osg::Matrixd::rotate(m_vRotation[0],osg::X_AXIS,m_vRotation[1],osg::Y_AXIS,m_vRotation[2],osg::Z_AXIS)*mat);
}

bool SimpleTraveller::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*> (&us);

	switch(ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		{
			if (ea.getKey() == 'w' || ea.getKey() == 'W')
			{
				changePosition(osg::Vec3d(m_iStep*cosf(osg::PI_2+m_vRotation._v[2]),m_iStep*sinf(osg::PI_2+m_vRotation._v[2]),0.0f));
			}
			else if (ea.getKey() == 's' || ea.getKey() == 'S')
			{
				changePosition(osg::Vec3d(-m_iStep*cosf(osg::PI_2+m_vRotation._v[2]),-m_iStep*sinf(osg::PI_2+m_vRotation._v[2]),0.0f));
			}
			else if (ea.getKey() == 'a' || ea.getKey() == 'A')
			{
				changePosition(osg::Vec3(-m_iStep*sinf(osg::PI_2+m_vRotation._v[2]),m_iStep*cosf(osg::PI_2+m_vRotation._v[2]),0));
			}
			else if (ea.getKey() == 'd' || ea.getKey() == 'D')
			{
				changePosition(osg::Vec3(m_iStep*sinf(osg::PI_2+m_vRotation._v[2]),-m_iStep*cosf(osg::PI_2+m_vRotation._v[2]),0));
			}
			else if (ea.getKey() == '+')
			{
				setStep(1);
			}
			else if (ea.getKey() == '-')
			{
				setStep(-1);
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Home)
			{
				changePosition(osg::Vec3(0.0f,0.0f,1.0f));
			}
			else if (ea.getKey() == osgGA::GUIEventAdapter::KEY_End)
			{
				changePosition(osg::Vec3(0.0f,0.0f,-1.0f));
			}
		}
		break;
	case osgGA::GUIEventAdapter::PUSH:
		{
			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				m_iLeftX = ea.getX();
				m_iLeftY = ea.getY();
				m_bLeftDown = true;
			}
			return false;
		}
		break;
	case osgGA::GUIEventAdapter::DRAG:
		{
			if(m_bLeftDown)
			{
				int delX = ea.getX() - m_iLeftX;
				int delY = ea.getY() - m_iLeftY;
				
				m_vRotation[2] -= osg::DegreesToRadians(m_fRotateStep*delX);
				m_vRotation[0] += osg::DegreesToRadians(m_fRotateStep*delY);

				if (m_vRotation[0] <= 0)
				{
					m_vRotation[0] = 0;
				}
				if (m_vRotation[0] >= osg::PI)
				{
					m_vRotation[0] = osg::PI;
				}
			}
		}
		break;
	case osgGA::GUIEventAdapter::RELEASE:
		{
			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				m_bLeftDown = false;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

bool SimpleTraveller::changePosition(osg::Vec3 delta)
{
	m_vPosition += delta;
	return true;
}

void SimpleTraveller::setStep(int delta_step)
{
	m_iStep += delta_step;
	if (m_iStep <= 0)
		m_iStep = 0;
}

