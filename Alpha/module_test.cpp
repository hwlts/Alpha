#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <string>

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/Math>
#include <osg/Matrixd>
#include <osg/MatrixTransform>
#include <osg/Vec3d>
#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osg/NodeCallback>
#include <osgGA/TrackballManipulator>
#include <osg/Switch>
#include <osg/DeleteHandler>

#include <osgViewer/CompositeViewer>
#include <osgGA/StateSetManipulator>
#include <osg/ImageSequence>


#include <stdio.h>
#include <string>

#include <Windows.h>


#include "PickHandler.h"
#include "TransformAccumulator.h"

using   namespace   std;

float x_trans=0;
float y_trans=0;
float z_trans=0;
float x_rot=0;
float y_rot=0;
float z_rot=0;

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:

    KeyboardEventHandler()
    {}
	~KeyboardEventHandler()
	{}

    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{    
	  // osgViewer::View *view = dynamic_cast<osgViewer::View*>( &aa );
	   
	   switch (ea.getEventType())
        {

			//鼠标按下
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
	
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osgText::Text> updatetext = new osgText::Text();
	CreateHUD *hudText= new CreateHUD();

	
	root->addChild(node.get());
	root->addChild(hudText->createHUD(updatetext.get()));

	
	viewer->addEventHandler(new CPickHandler(updatetext.get()));

	//viewer->setUpViewInWindow(80,40,1024,680);
	viewer->setSceneData(root.get());
	viewer->addEventHandler(new KeyboardEventHandler);


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



		// 设置视口矩阵（旋转矩阵和平移矩阵连乘）。
		viewer->getCamera()->setViewMatrix( m_x_rot*m_y_rot*m_z_rot*trans );
		// 绘制下一帧
		viewer->frame();
	}
}