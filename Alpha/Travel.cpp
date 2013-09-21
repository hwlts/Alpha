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
	//����Viewer����
	osg::ref_ptr<osgViewer::Viewer>viewer = new osgViewer::Viewer();

	//���״̬�¼�
	//viewer.get()->addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
	//���ڴ�С�仯�¼�
	//viewer.get()->addEventHandler(new osgViewer::WindowSizeHandler);
	//���һЩ����״̬����
	//viewer.get()->addEventHandler(new osgViewer::StatsHandler);

	// �����������뵽������
	TravelManipulator::TravelToScence(viewer.get());

	osg::ref_ptr<osg::Group>root = new osg::Group();

	// ��ȡ����
	osg::ref_ptr<osg::Node>node = osgDB::readNodeFile("E:\\OSG_Resource\\FLT\\Sample\\Data\\Vega\\town.flt");

	// ��ȡ�ɻ�
	//osg::ref_ptr<osg::Node>tank = osgDB::readNodeFile("F://Models//Amx30//Amx30.IVE");
	osg::ref_ptr<osg::Node>B25 = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr < osg::MatrixTransform> scale = new osg::MatrixTransform ;
	scale ->setMatrix(osg::Matrix::scale(0.1, 0.1, 0.1)*osg::Matrix::translate(-10.0f, -250.0f, 99.0f)) ;
	scale ->addChild(B25.get()) ;

	// ��ӵ�����
	root->addChild(node.get());
	root->addChild(scale.get());
	//root->addChild(B25.get());

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());




	viewer->realize();

	viewer->run();

	return 0;
	
}

