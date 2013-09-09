#include "SimpleTraveller.h"

SimpleTraveller::SimpleTraveller() :
	m_vPosition(osg::Vec3(0.0f,0.0f,5.0f)),
	m_vRotation(osg::Vec3(osg::PI_2,0.0f,0.0f)),
	m_iStep(1.0f),
	m_fRotateStep(0) {}

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
				changePosition(osg::Vec3(0.0f,m_vStep,0.0f));
			}
			else if (ea.getKey() == 's' || ea.getKey() == 'S')
			{
				changePosition(osg::Vec3(0.0f,-m_vStep,0.0f));
			}
			else if (ea.getKey() == 'a' || ea.getKey() == 'A')
			{
				changePosition(osg::Vec3(-m_vStep,0.0f,0.0f));
			}
			else if (ea.getKey() == 'd' || ea.getKey() == 'D')
			{
				changePosition(osg::Vec3(m_vStep,0.0f,0.0f));
			}
		}
		break;
	}
	return false;
}

bool SimpleTraveller::changePosition(osg::Vec3 delta)
{
	m_vPosition += delta;
	return true;
}

