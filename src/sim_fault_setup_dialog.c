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
// The Fault Simulation Setup dialog allows the user to //
// set the parameters for fault simulations.            //
//                                                      //
//DAYANE ALFENAS REIS                                   //
//////////////////////////////////////////////////////////

#include <stdlib.h>
#include <gtk/gtk.h>

#include "support.h"
//#include "fault_simulation.h"
#include "sim_fault_setup_dialog.h"
#include "file_selection_window.h"

//static fault_simulation_OP fault_simulation_options =
//{100,
// FALSE,
// FALSE,
// FALSE,
// TRUE,
// "teste"} ;
//psz = get_file_name_from_user (NULL, _("Select Output Files Path"), NULL, FALSE);

typedef struct
  {
  GtkWidget *sim_fault_setup_dialog;
  GtkWidget *dialog_vbox1;
  GtkWidget *table;
  GtkWidget *label1;
  GtkWidget *label3;
  GtkWidget *number_of_simulations_entry;
  GtkWidget *chkVacancy;
  GtkWidget *chkInterstitial;
  GtkWidget *chkDopant;
  GtkWidget *chkDislocation;
  GtkWidget *action_area;
  GtkWidget *sim_fault_setup_dialog_ok_button;
  GtkWidget *sim_fault_setup_dialog_cancel_button;
  } sim_fault_setup_dialog_D;

static sim_fault_setup_dialog_D sim_fault_setup_dialog = {NULL};

static void create_sim_fault_setup_dialog (sim_fault_setup_dialog_D *dialog, fault_simulation_OP *pbo) ;
static void output_path_button_clicked(GtkButton *button, fault_simulation_OP *pbo);

void get_sim_fault_from_user (GtkWindow *parent, fault_simulation_OP *pbo)
  {

  char sz[16] = "" ;
  if (NULL == sim_fault_setup_dialog.sim_fault_setup_dialog)
    create_sim_fault_setup_dialog (&sim_fault_setup_dialog, pbo) ;

  gtk_window_set_transient_for (GTK_WINDOW (sim_fault_setup_dialog.sim_fault_setup_dialog), parent) ;

  g_snprintf (sz, 16, "%d", pbo->number_of_simulations) ;
  gtk_entry_set_text (GTK_ENTRY (sim_fault_setup_dialog.number_of_simulations_entry), sz) ;

 // g_snprintf (sz, 16, "%c", pbo->output_files_path) ;
 // gtk_entry_set_text (GTK_ENTRY (sim_fault_setup_dialog.output_files_path_entry), sz) ;

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkVacancy),
    pbo->vacancy) ;

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkInterstitial),
    pbo->interstitial) ;

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkDopant),
    pbo->dopant) ;

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkDislocation),
    pbo->dislocation) ;

  if (GTK_RESPONSE_OK == gtk_dialog_run (GTK_DIALOG (sim_fault_setup_dialog.sim_fault_setup_dialog)))
    {
    pbo->number_of_simulations =         atoi (gtk_entry_get_text (GTK_ENTRY (sim_fault_setup_dialog.number_of_simulations_entry))) ;
    pbo->vacancy =           gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkVacancy)) ;
    pbo->interstitial =        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkInterstitial)) ;
    pbo->dopant =           gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkDopant)) ;
    pbo->dislocation =        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (sim_fault_setup_dialog.chkDislocation)) ;
    }

  gtk_widget_hide (sim_fault_setup_dialog.sim_fault_setup_dialog) ;

  if (NULL != parent)
    gtk_window_present (parent) ;
  }

static void create_sim_fault_setup_dialog (sim_fault_setup_dialog_D *dialog, fault_simulation_OP *pbo)
  {
  GtkWidget *hbox = NULL, *lbl = NULL ;

  if (NULL != dialog->sim_fault_setup_dialog) return ;

  dialog->sim_fault_setup_dialog = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog->sim_fault_setup_dialog), _("Fault Simulation Setup"));
  gtk_window_set_resizable (GTK_WINDOW (dialog->sim_fault_setup_dialog), FALSE);
  gtk_window_set_modal (GTK_WINDOW (dialog->sim_fault_setup_dialog), TRUE) ;

  dialog->dialog_vbox1 = GTK_DIALOG (dialog->sim_fault_setup_dialog)->vbox;
  gtk_widget_show (dialog->dialog_vbox1);

  dialog->table = gtk_table_new (9, 3, FALSE);
  gtk_widget_show (dialog->table);
  gtk_container_set_border_width (GTK_CONTAINER (dialog->table), 2);
  gtk_box_pack_start (GTK_BOX (dialog->dialog_vbox1), dialog->table, TRUE, TRUE, 0);

  dialog->label1 = gtk_label_new (_("Number Of Simulations:"));
  gtk_widget_show (dialog->label1);
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->label1, 0, 1, 0, 1,
		  (GtkAttachOptions) (GTK_SHRINK),
		  (GtkAttachOptions) (GTK_SHRINK), 2, 2);
  gtk_label_set_justify (GTK_LABEL (dialog->label1), GTK_JUSTIFY_LEFT);
  gtk_misc_set_alignment (GTK_MISC (dialog->label1), 1, 0.5);

  dialog->number_of_simulations_entry = gtk_entry_new ();
  gtk_widget_show (dialog->number_of_simulations_entry);
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->number_of_simulations_entry, 0, 1, 1, 2,
		  (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
		  (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 2, 2);
  gtk_entry_set_activates_default (GTK_ENTRY (dialog->number_of_simulations_entry), TRUE) ;

    dialog->label3 = gtk_label_new (_("Faults to be simulated:"));
  gtk_widget_show (dialog->label3);
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->label3, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_SHRINK),
                    (GtkAttachOptions) (GTK_SHRINK), 2, 2);
  gtk_label_set_justify (GTK_LABEL (dialog->label3), GTK_JUSTIFY_LEFT);
  gtk_misc_set_alignment (GTK_MISC (dialog->label3), 1, 0.5);

  dialog->chkVacancy = gtk_check_button_new_with_label (_("Vacancy")) ;
  gtk_widget_show (dialog->chkVacancy) ;
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->chkVacancy, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 2, 2);

  dialog->chkInterstitial = gtk_check_button_new_with_label (_("Interstitial")) ;
  gtk_widget_show (dialog->chkInterstitial) ;
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->chkInterstitial, 0, 1, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 2, 2);

  dialog->chkDopant = gtk_check_button_new_with_label (_("Dopant")) ;
  gtk_widget_show (dialog->chkDopant) ;
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->chkDopant, 0, 1, 5, 6,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 2, 2);

  dialog->chkDislocation = gtk_check_button_new_with_label (_("Dislocation")) ;
  gtk_widget_show (dialog->chkDislocation) ;
  gtk_table_attach (GTK_TABLE (dialog->table), dialog->chkDislocation, 0, 1, 6, 7,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 2, 2);



  gtk_dialog_add_button (GTK_DIALOG (dialog->sim_fault_setup_dialog), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL) ;
  gtk_dialog_add_button (GTK_DIALOG (dialog->sim_fault_setup_dialog), GTK_STOCK_OK, GTK_RESPONSE_OK) ;
  gtk_dialog_set_default_response (GTK_DIALOG (dialog->sim_fault_setup_dialog), GTK_RESPONSE_OK) ;
 }

