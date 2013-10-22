#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Math>
#include <osg/Image>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/TerrainManipulator>

#include<osgDB/ReadFile>
#include<osgDB/WriteFile>

#include<osgUtil/Optimizer>


#include "SimpleTraveller.h"
#include "CreatePath.h"
#include "PickHandler.h"

/************************************************************************/
/* town.flt Version
/************************************************************************/

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	//捕捉鼠标坐标
	osg::ref_ptr<osgText::Text> updatetext = new osgText::Text();
	CreateHUD *hudText= new CreateHUD();

	root->addChild(hudText->createHUD(updatetext.get()));

	viewer->addEventHandler(new CPickHandler(updatetext.get()));

	//模型加入场景
	osgDB::Registry::instance()->setOptions(new osgDB::Options("dds_flip"));
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("C:\\Users\\Administrator\\Desktop\\boston_flt_dds\\master.flt");
	root->addChild(node.get());
	viewer->setSceneData(root.get());

	//加入su37的固定路径漫游
	osg::AnimationPath*  su37_Path = CreatePath::testPath();
	su37_Path->setLoopMode(osg::AnimationPath::LOOP);
	osg::ref_ptr<osg::MatrixTransform> su37 = new osg::MatrixTransform();



	osg::ref_ptr<osg::Node> su37_node = osgDB::readNodeFile("E:\\OSG_Resource\\FLT\\Gallery\\Models\\f35a.flt");
	//su37->addChild(su37_node);
	su37->setUpdateCallback(new osg::AnimationPathCallback(su37_Path));
	root->addChild(su37);

	osg::ref_ptr<osg::MatrixTransform> su370= new osg::MatrixTransform();
	osg::ref_ptr<osg::MatrixTransform> su371 = new osg::MatrixTransform();
	osg::ref_ptr<osg::MatrixTransform> su372 = new osg::MatrixTransform();

	su370->setMatrix(osg::Matrix::translate(0,10,0));
	su371->setMatrix(osg::Matrix::translate(5,0,0));
	su372->setMatrix(osg::Matrix::translate(-5,0,0));

	su370->addChild(su37_node);
	su371->addChild(su37_node);
	su372->addChild(su37_node);

	su37->addChild(su370);
	su37->addChild(su371);
	su37->addChild(su372);


	//自定义漫游器加入场景
	SimpleTraveller * st = new SimpleTraveller();
	st->setMnode(root);
	//st->setPosition(osg::Vec3(2580,2330,2));
	viewer->setCameraManipulator(st);

	return viewer->run();
}

