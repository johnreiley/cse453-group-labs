/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, John Reiley
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#include "control.h" // the header file 

/******************************************
 * A map of control name to value mappings
 * used by controlToEnum()
 ******************************************/
const std::map<const std::string, const Control> ControlMap =
{
    {"Confidential", CONFIDENTIAL},
    {"Secret", SECRET},
    {"Privileged", PRIVILEGED},
    {"Public", PUBLIC}
};


// R - request for access to an object
/**************************************
* Determines whether or not the user
* has read access to a given asset
* according to Bell-LaPadula
**************************************/
bool securityControlRead(Control assetControl, Control subjectControl) // A - access attributes
{
   // D - decision or result of the request
   return subjectControl >= assetControl;
}


// R - request for access to an object
/**************************************
* Determines whether or not the user
* has write access to a given asset,
* according to Bell-LaPadula
**************************************/
bool securityControlWrite(Control assetControl, Control subjectControl) // A - access attributes
{
   // D - decision or result of the request
   return subjectControl <= assetControl;
}

/*******************************************
 * Convert a text control value to its 
 * representative access-control level
 *******************************************/
const Control convertToEnum(const std::string textControl)
{
    return ControlMap.at(textControl);
}
