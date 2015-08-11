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
// The fault simulation.                                //
//                                                      //
//                                                      //
//                                                      //
//////////////////////////////////////////////////////////

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef GTK_GUI
  #include "callback_helpers.h"
  #include "support.h"
#else
  #define _(s) s
#endif /* def GTK_GUI */
#include "objects/QCADCell.h"
#include "custom_widgets.h"
#include "global_consts.h"
#include "fault_simulation.h"

//#define REDUCE_DEREF

//!Options for the fault simulation engine
//This variable is used by multiple source files
extern fault_simulation_OP fault_simulation_options = {100, FALSE, FALSE, FALSE, TRUE, '/home/dayane/QCADesigner-2.0.3/simulation_results/dayane'} ;

