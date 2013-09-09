#pragma once

#include<osgGA/CameraManipulator>
#include<osgViewer/Viewer>

class SimpleTraveller : public osgGA::CameraManipulator
{
public:
	
	SimpleTraveller();
	~SimpleTraveller();

	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix() const;

	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getInverseMatrix() const; 

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

	bool changePosition(osg::Vec3 delta);

	void setStep(int delta_step);

private:
	
	osg::Vec3 m_vPosition;

	osg::Vec3 m_vRotation;

	int m_iStep;

	float m_fRotateStep;

	int m_iLeftX;
	
	int m_iLeftY;

	bool m_bLeftDown;

};