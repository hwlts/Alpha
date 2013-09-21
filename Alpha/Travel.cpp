/*
 * File        : Travel.cpp
 * Description : 
 * Author      : GuoShaoHao
 * E-mail      : gsh0913@qq.com
 * Date        : 2011/01/08
 * 
 * CopyRight @ South China Institute of Software Engineering,.GZU
 *
 */

#include <iostream>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <osg/MatrixTransform>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

#include "TravelManipulator.h"

using namespace std;


int main()
{
	//创建Viewer对象
	osg::ref_ptr<osgViewer::Viewer>viewer = new osgViewer::Viewer();

	//添加状态事件
	//viewer.get()->addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
	//窗口大小变化事件
	//viewer.get()->addEventHandler(new osgViewer::WindowSizeHandler);
	//添加一些常用状态设置
	//viewer.get()->addEventHandler(new osgViewer::StatsHandler);

	// 把漫游器加入到场景中
	TravelManipulator::TravelToScence(viewer.get());

	osg::ref_ptr<osg::Group>root = new osg::Group();

	// 读取地形
	osg::ref_ptr<osg::Node>node = osgDB::readNodeFile("E:\\OSG_Resource\\FLT\\Sample\\Data\\Vega\\town.flt");

	// 读取飞机
	//osg::ref_ptr<osg::Node>tank = osgDB::readNodeFile("F://Models//Amx30//Amx30.IVE");
	osg::ref_ptr<osg::Node>B25 = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr < osg::MatrixTransform> scale = new osg::MatrixTransform ;
	scale ->setMatrix(osg::Matrix::scale(0.1, 0.1, 0.1)*osg::Matrix::translate(-10.0f, -250.0f, 99.0f)) ;
	scale ->addChild(B25.get()) ;

	// 添加到场景
	root->addChild(node.get());
	root->addChild(scale.get());
	//root->addChild(B25.get());

	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());




	viewer->realize();

	viewer->run();

	return 0;
	
}

