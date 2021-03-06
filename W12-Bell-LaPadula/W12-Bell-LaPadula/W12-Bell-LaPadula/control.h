/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, John Reiley, Justen Neeley, Benjamin Hansen
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once

#include <string>
#include <map>
	
// C - classification of security levels
enum Control {
   PUBLIC, 
   CONFIDENTIAL, 
   PRIVILEGED, 
   SECRET
};


// R - request for access to an object
/**************************************
* Determines whether or not the user
* has read access to a given asset
* according to Bell-LaPadula
**************************************/
bool securityControlRead(Control assetControl, Control subjectControl);

// R - request for access to an object
/**************************************
* Determines whether or not the user
* has write access to a given asset,
* according to Bell-LaPadula
**************************************/
bool securityControlWrite(Control assetControl, Control subjectControl);

/*******************************************
 * Convert a text control value to its 
 * representative access-control level
 *******************************************/
const Control convertToEnum(const std::string textControl);
