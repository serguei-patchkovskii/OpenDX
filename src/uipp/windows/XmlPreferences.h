/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 2004                                        */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _XmlPreferences_h
#define _XmlPreferences_h

#include <vcclr.h>

using namespace System;
using namespace System::Xml;

class XmlPreferences {
private:
	gcroot<XmlDocument *> prefs;
	bool fileExisted;
	gcroot<XmlNode *> root;

protected:
		XmlPreferences();
		~XmlPreferences();
public:
	enum PrefType { TypeString, TypeInt, TypeBool, TypeFloat };
	void BuildTheXmlPreferences(void);
	bool readPrefs(const char *filename);
	bool createPrefs();
	bool writePrefs(const char *filename);

	// getPref looks for prefName in the Xml document. If found, will 
	// allocate value and set it. Returns true if found false otherwise.
	// Will require that return be deleted unless this class is rewritten
	// to be _gc.
	bool getPref(const char *prefName, char*& value);
	bool getPref(const char *prefName, PrefType &type, char*& value);
	bool getPref(const char *prefName, bool &value);
	bool getPref(const char *prefName, int &value);

	// setPref will override the current *prefName in the XmlDocument so
	// that the new pref will be written to the prefs file. 
	bool setPref(const char *prefName, const char* value, bool persist=false);
	bool setPref(const char *prefName, PrefType type, const char* value, bool persist=false);

	// setDefault will only add *prefName to the XmlDocument if it is 
	// not already set in the prefs file. This is necessary 
	bool setDefault(const char *prefName, const char* value);
	bool setDefault(const char *prefName, PrefType type, const char* value);

};

extern XmlPreferences *theXmlPreferences;

#endif // _XmlPreferences_h 