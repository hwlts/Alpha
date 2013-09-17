#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Math>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/TerrainManipulator>

#include<osgDB/ReadFile>
#include<osgDB/WriteFile>

#include<osgUtil/Optimizer>

#include "TravelManipulator.h"
#include "SimpleTraveller.h"
#include "createPath.h"
#include "KeyBoardHandler.h"
#include "PickHandler.h"

float x_trans=0;
float y_trans=0;
float z_trans=0;
float x_rot=0;
float y_rot=0;
float z_rot=0;

class l_KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:

	l_KeyboardEventHandler()
	{}
	~l_KeyboardEventHandler()
	{}

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{    
		// osgViewer::View *view = dynamic_cast<osgViewer::View*>( &aa );

		switch (ea.getEventType())
		{

			//Êó±ê°´ÏÂ
		case(osgGA::GUIEventAdapter::PUSH):
			{
			}


		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				switch (ea.getKey())
				{
				case 'q':
					x_trans++;
					return true;
				case 'a': 
					x_trans--;
					return true;
				case 'w':
					y_trans++;
					return true;
				case 's':
					y_trans--;
					return true;
				case 'e':
					z_trans++;
					return true;
				case 'd':
					z_trans--;
					return true;



				case 'r':
					x_rot+=0.1;
					return true;
				case 'f':
					x_rot-=0.1;
					return true;
				case 't':
					y_rot+=0.1;
					return true;
				case 'g': 
					y_rot-=0.1;
					return true;
				case 'y':
					z_rot+=0.1;
					return true;
				case 'h':
					z_rot-=0.1;
					return true;


				}
			}
		default:
			break;

		}
		//return false to allow mouse manipulation
		return false;
	}

};

int main()
{
	//osg::ref_ptr<osgViewer::Viewer> viewer =  new osgViewer::Viewer();

	//osg::ref_ptr<osg::Group> root  = new osg::Group();

	//osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("cessna.osg");
	// 
	//osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:\\FLT\\Sample\\Data\\Vega\\town.flt");

	//const osg::BoundingSphere& bs = cessna->getBound();
	//osg::Vec3 position = bs.center() + osg::Vec3(0.0f,0.0f,200.0f);
	//float size = 100.0f/bs.radius()*0.3f;

	//osg::ref_ptr<osg::AnimationPath> animationPath =  new osg::AnimationPath();
	//animationPath = createAnimationPath(position,200.0f,10.0f);

	//osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();

	//mt->setDataVariance(osg::Object::STATIC);

	//mt->setMatrix(osg::Matrix::translate(-bs.center())*osg::Matrix::scale(size,size,size)*osg::Matrix::rotate(osg::inDegrees(-180.0f),0.0f,0.0f,1.0f));

	//mt->addChild(cessna.get());

	//osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	//pat->setUpdateCallback(new osg::AnimationPathCallback(animationPath.get(),0.0f,1.0f));
	//pat->addChild(mt);

	//root->addChild(pat.get());
	//root->addChild(node.get());

	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(root.get());

	//viewer->setSceneData(root.get());

	//viewer->addEventHandler(new KeyBoardHandler());

	//osg::ref_ptr<osgGA::DriveManipulator> p = new osgGA::DriveManipulator();

	//viewer->setCameraManipulator(p);

	//viewer->realize();

	//viewer->run();

	//return 0;

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();


	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:\\FLT\\Sample\\Data\\Vega\\town.flt");

	osg::ref_ptr<osgText::Text> updatetext = new osgText::Text();
	CreateHUD *hudText= new CreateHUD();


	root->addChild(node.get());
	root->addChild(hudText->createHUD(updatetext.get()));


	viewer->addEventHandler(new CPickHandler(updatetext.get()));

	//viewer->setUpViewInWindow(80,40,1024,680);
	viewer->setSceneData(root.get());
	viewer->addEventHandler(new l_KeyboardEventHandler);


	while (!viewer->done())
	{
		osg::Matrix trans;
		trans.makeTranslate( x_trans, y_trans, z_trans );

		osg::Matrix m_x_rot;
		m_x_rot.makeRotate( x_rot, osg::Vec3( 1., 0., 0. ) );

		osg::Matrix m_y_rot;
		m_y_rot.makeRotate( y_rot, osg::Vec3(0., 1., 0. ) );

		osg::Matrix m_z_rot;
		m_z_rot.makeRotate( z_rot, osg::Vec3( 0.,0., 1. ) );



		// ÉèÖÃÊÓ¿Ú¾ØÕó£¨Ðý×ª¾ØÕóºÍÆ½ÒÆ¾ØÕóÁ¬³Ë£©¡£
		viewer->getCamera()->setViewMatrix( m_x_rot*m_y_rot*m_z_rot*trans );
		// »æÖÆÏÂÒ»Ö¡
		viewer->frame();
	}

}

//int main(int argc, char** argv)
//{
//	//创建Viewer对象，场景浏览器
//	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
//
//	//把漫游器加入到场景中
//	viewer->setCameraManipulator(new SimpleTraveller());
//
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//
//	//读取地形模型
//	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("lz.osg");
//
//	//添加到场景
//	root->addChild(node.get());
//
//	//优化场景数据
//	osgUtil::Optimizer optimizer;
//	optimizer.optimize(root.get());
//
//	viewer->setSceneData(root.get());
//	viewer->realize();
//	viewer->run();
//
//	return 0;
//}
