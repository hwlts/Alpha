#ifndef CREATEPATH_H
	#define  CREATEPATH_H

#include <osg/AnimationPath>
#include <osg/Math>
#include <osg/Vec3>

class CreatePath
{
	typedef osg::AnimationPath::ControlPoint ControlPoint;

public:
	static osg::AnimationPath* testPath();
};

#endif