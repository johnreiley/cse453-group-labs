/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, John Reiley
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once
// #pragma once won't work for Benjamin's compiler (on Linux) ... sorry.
//#ifndef CONTROL_H
//#define CONTROL_H


// C - classification of security levels
enum Control {
   PUBLIC, 
   CONFIDENTIAL, 
   PRIVILEDGED, 
   SECRET
};


// R - request for access to an object
/**************************************
* Determines whether or not the user
* has read access to a given asset
* according to Bell-LaPadula
**************************************/
bool securityControlRead(Control assetControl, Control subjectControl); // A - access attributes


// R - request for access to an object
/**************************************
* Determines whether or not the user
* has write access to a given asset,
* according to Bell-LaPadula
**************************************/
bool securityControlWrite(Control assetControl, Control subjectControl); // A - access attributes

//#endif // CONTROL_H
