#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgGA/DriveManipulator>
#include <osgViewer/Viewer>

/*key board handler Desktop*/ 
class KeyboardHandler : public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
								osgGA::GUIActionAdapter& aa,
								osg::Object*, osg::NodeVisitor*)
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*> (&aa);
		
		if (!viewer)
			return false;

		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)
			{
				int width = ea.getWindowWidth();
				int height = ea.getWindowHeight();
				viewer->requestWarpPointer(width*0.5,height*0.5);
			}
			else
			{
				osg::Switch* root = dynamic_cast<osg::Switch*>(viewer->getSceneData());
				if (!root)
					return false;
				
				if (ea.getKey()=='1')
				{
					root->setValue(0,true);
					root->setValue(1,false);
				}
				else if (ea.getKey()=='2')
				{
					root->setValue(0,false);
					root->setValue(1,true);
				}
				return true;
			}
			break;
		default:break;
		}
	return false;
	}
};

/*c*/
int main(int argc, char** argv)
{

	//osg::ref_ptr<osg::Switch> root = new osg::Switch;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(osgDB::readNodeFile("E:\\OSG_Resource\\FLT\\Sample\\Data\\Vega\\town.flt"));
	//root->addChild(osgDB::readNodeFile("cessnafire.osg"),false);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	//viewer.addEventHandler(new KeyboardHandler);
	viewer.setCameraManipulator(new osgGA::DriveManipulator);
	return viewer.run();
}
