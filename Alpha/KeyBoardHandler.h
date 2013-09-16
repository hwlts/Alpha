#ifndef KEYBOARDHANDLER_H
	#define KEYBOARDHANDLER_H

#include <osgViewer/Viewer>

#include <osgGA/GUIEventHandler>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>

class KeyBoardHandler : public osgGA::GUIEventHandler
{
public:

	virtual bool handle(const osgGA::GUIEventAdapter &ea,
							  osgGA::GUIActionAdapter &aa,
							  osg::Object*,
							  osg::NodeVisitor*);
};

#endif