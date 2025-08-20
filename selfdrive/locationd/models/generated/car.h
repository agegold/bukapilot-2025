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
void car_err_fun(double *nom_x, double *delta_x, double *out_8269961610171249386);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2224385476887686460);
void car_H_mod_fun(double *state, double *out_4022147246895696966);
void car_f_fun(double *state, double dt, double *out_6384510303045167306);
void car_F_fun(double *state, double dt, double *out_8622433723209998390);
void car_h_25(double *state, double *unused, double *out_325406975583737227);
void car_H_25(double *state, double *unused, double *out_7545127896885188643);
void car_h_24(double *state, double *unused, double *out_8037109127115793444);
void car_H_24(double *state, double *unused, double *out_7343690578022039837);
void car_h_30(double *state, double *unused, double *out_8088672232404409668);
void car_H_30(double *state, double *unused, double *out_7415788949741948573);
void car_h_26(double *state, double *unused, double *out_7145162379502747233);
void car_H_26(double *state, double *unused, double *out_3803624578011132419);
void car_h_27(double *state, double *unused, double *out_3362193027028069912);
void car_H_27(double *state, double *unused, double *out_5241025637941523662);
void car_h_29(double *state, double *unused, double *out_3086998964743564023);
void car_H_29(double *state, double *unused, double *out_3527662911071972629);
void car_h_28(double *state, double *unused, double *out_5966598347836767563);
void car_H_28(double *state, double *unused, double *out_5491293182637298880);
void car_h_31(double *state, double *unused, double *out_8206679626337786412);
void car_H_31(double *state, double *unused, double *out_7575773858762149071);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}