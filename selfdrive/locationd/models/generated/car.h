#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_54115344297803870);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_486023171127865793);
void car_H_mod_fun(double *state, double *out_741897642024606427);
void car_f_fun(double *state, double dt, double *out_2982029055930059059);
void car_F_fun(double *state, double dt, double *out_6513532347961345036);
void car_h_25(double *state, double *unused, double *out_3229136396796182411);
void car_H_25(double *state, double *unused, double *out_9092266040851434872);
void car_h_24(double *state, double *unused, double *out_1430429500839531180);
void car_H_24(double *state, double *unused, double *out_3280880409828657907);
void car_h_30(double *state, double *unused, double *out_281410406440697450);
void car_H_30(double *state, double *unused, double *out_2175575699359818117);
void car_h_26(double *state, double *unused, double *out_2531141696829155933);
void car_H_26(double *state, double *unused, double *out_5787740071090634271);
void car_h_27(double *state, double *unused, double *out_5833541717604880062);
void car_H_27(double *state, double *unused, double *out_4350339011160243028);
void car_h_29(double *state, double *unused, double *out_4720262861220148195);
void car_H_29(double *state, double *unused, double *out_6063701738029794061);
void car_h_28(double *state, double *unused, double *out_7209432301142177531);
void car_H_28(double *state, double *unused, double *out_7300643318610226981);
void car_h_31(double *state, double *unused, double *out_7336335026159320020);
void car_H_31(double *state, double *unused, double *out_2015590790339617619);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}