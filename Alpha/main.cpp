#include <osg/io_utils>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <iostream>

class RotateCallback : public osg::NodeCallback
{
public:
	RotateCallback() : _rotateZ(0.0) {}

	virtual void operator() (osg::Node* node, osg::NodeVisitor* nv)
	{
		osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);

		if(pat)
		{
			osg::Quat quat(osg::DegreesToRadians(_rotateZ),osg::Z_AXIS);
			pat->setAttitude(quat);
			_rotateZ+=1.0;
		}

		traverse(node,nv);
	}

protected:
	double _rotateZ;
};
