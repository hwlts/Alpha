#include "KeyBoardHandler.h"

bool KeyBoardHandler::handle(const osgGA::GUIEventAdapter &ea,
										  osgGA::GUIActionAdapter &aa,
									      osg::Object*,
										  osg::NodeVisitor*)
{
	osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*> (&aa);

	if (!viewer)
	{
		return false;
	}

	switch(ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:
		{
			if (ea.getKey() == 'c' || ea.getKey() == 'C')
			{
				viewer->setCameraManipulator(new osgGA::TerrainManipulator());
			}
			else if (ea.getKey() == 'v' || ea.getKey() == 'V')
			{
				viewer->setCameraManipulator(new osgGA::DriveManipulator());
			}
				return true;
			break;
		}
	default:
		break;
	}

	return false;
}