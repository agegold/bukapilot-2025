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
void car_err_fun(double *nom_x, double *delta_x, double *out_7009082287290678410);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6773512853317553183);
void car_H_mod_fun(double *state, double *out_5453048751080424150);
void car_f_fun(double *state, double dt, double *out_2696784723507792136);
void car_F_fun(double *state, double dt, double *out_2855698406566993747);
void car_h_25(double *state, double *unused, double *out_4410045275916909057);
void car_H_25(double *state, double *unused, double *out_5072357289655267661);
void car_h_24(double *state, double *unused, double *out_6567175883780815729);
void car_H_24(double *state, double *unused, double *out_1514431690852944525);
void car_h_30(double *state, double *unused, double *out_6497667489146449420);
void car_H_30(double *state, double *unused, double *out_2554024331148019034);
void car_h_26(double *state, double *unused, double *out_1142086035247273555);
void car_H_26(double *state, double *unused, double *out_8813860608529323885);
void car_h_27(double *state, double *unused, double *out_7222597379186762440);
void car_H_27(double *state, double *unused, double *out_4728787642948443945);
void car_h_29(double *state, double *unused, double *out_6947403316902256551);
void car_H_29(double *state, double *unused, double *out_2043792986833626850);
void car_h_28(double *state, double *unused, double *out_1344311891628047352);
void car_H_28(double *state, double *unused, double *out_7126192003903157424);
void car_h_31(double *state, double *unused, double *out_2585023898607921181);
void car_H_31(double *state, double *unused, double *out_9006675362946876255);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}