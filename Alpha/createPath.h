#ifndef CREATEPATH_H
	#define  CREATEPATH_H

#include <osg/AnimationPath>
#include <osg/Math>
#include <osg/Vec3>

osg::ref_ptr<osg::AnimationPath> createAnimationPath(osg::Vec3 & center, float radius, float looptime);

#endif