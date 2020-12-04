/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, John Reiley
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#include "control.h" // the header file 

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
