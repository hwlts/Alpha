#include "createPath.h"

osg::AnimationPath* CreatePath::testPath()
{
	
	osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath();

	osg::Vec3 v0(2000,2000,200);
	osg::Vec3 v01(2001,2000,200);
	osg::Vec3 v1(2100,2000,200);
	osg::Vec3 v11(2100,2001,200);
	osg::Vec3 v2(2100,2100,200);
	osg::Vec3 v21(2099,2100,200);
	osg::Vec3 v3(2000,2100,200);
	osg::Vec3 v31(2000,2099,200);
	osg::Vec3 z_aix(0,0,1);
	path->insert(0.0,ControlPoint(v0,osg::Quat(osg::PI,z_aix)));
	path->insert(0.1,ControlPoint(v01,osg::Quat(osg::PI_2+osg::PI,z_aix)));
	path->insert(5.0,ControlPoint(v1,osg::Quat(osg::PI_2+osg::PI,z_aix)));
	path->insert(5.1,ControlPoint(v11,osg::Quat(0,z_aix)));
	path->insert(10.0,ControlPoint(v2,osg::Quat(0,z_aix)));
	path->insert(10.1,ControlPoint(v21,osg::Quat(osg::PI_2,z_aix)));
	path->insert(15.0,ControlPoint(v3,osg::Quat(osg::PI_2,z_aix)));
	path->insert(15.1,ControlPoint(v31,osg::Quat(osg::PI,z_aix)));
	path->insert(20.0,ControlPoint(v0,osg::Quat(osg::PI,z_aix)));
	return path.release();
}