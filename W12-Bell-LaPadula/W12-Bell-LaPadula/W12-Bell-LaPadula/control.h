/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, John Reiley, Justen Neeley, Benjamin Hansen
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/
	
/******************************************
 * A map of control name to value mappings
 * used by controlToEnum()
 ******************************************/
const std::map<std::string, Control> ControlMap =
{
    {"Confidential", CONFIDENTIAL},
    {"Secret", SECRET},
    {"Privileged", PRIVILEGED},
    {"Public", PUBLIC}
};


#pragma once
#include "string"
#include "map"
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
Control convertToEnum(std::string textControl);
