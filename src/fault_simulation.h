//////////////////////////////////////////////////////////
// QCADesigner                                          //
// Copyright 2002 Konrad Walus                          //
// All Rights Reserved                                  //
// Author: Konrad Walus                                 //
// Email: qcadesigner@gmail.com                         //
// WEB: http://qcadesigner.ca/                          //
//////////////////////////////////////////////////////////
//******************************************************//
//*********** PLEASE DO NOT REFORMAT THIS CODE *********//
//******************************************************//
// If your editor wraps long lines disable it or don't  //
// save the core files that way. Any independent files  //
// you generate format as you wish.                     //
//////////////////////////////////////////////////////////
// Please use complete names in variables and fucntions //
// This will reduce ramp up time for new people trying  //
// to contribute to the project.                        //
//////////////////////////////////////////////////////////
// Contents:                                            //
//                                                      //
// Header file for the fault simulation.                //
//                                                      //
//                                                      //
//                                                      //
//////////////////////////////////////////////////////////

#ifndef _FAULT_SIMULATION_H_
#define _FAULT_SIMULATION_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

typedef struct
  {
	int number_of_simulations;
	gboolean vacancy;
	gboolean interstitial;
	gboolean dopant;
	gboolean dislocation;
	gchar output_files_path;
  } fault_simulation_OP;

#endif /* _FAULT_SIMULATION_H_ */
