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
void car_err_fun(double *nom_x, double *delta_x, double *out_633373506833746237);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7027051672422316378);
void car_H_mod_fun(double *state, double *out_7746484100154490520);
void car_f_fun(double *state, double dt, double *out_23274275379461392);
void car_F_fun(double *state, double dt, double *out_7589757881269145047);
void car_h_25(double *state, double *unused, double *out_7885764047385617391);
void car_H_25(double *state, double *unused, double *out_1446704125757746717);
void car_h_24(double *state, double *unused, double *out_2881583653453946631);
void car_H_24(double *state, double *unused, double *out_601707516974051318);
void car_h_30(double *state, double *unused, double *out_5034922589772911112);
void car_H_30(double *state, double *unused, double *out_5469986215733870038);
void car_h_26(double *state, double *unused, double *out_5480592634709264249);
void car_H_26(double *state, double *unused, double *out_789850061647434813);
void car_h_27(double *state, double *unused, double *out_2155323206679707572);
void car_H_27(double *state, double *unused, double *out_3295222903933445127);
void car_h_29(double *state, double *unused, double *out_753358748529250604);
void car_H_29(double *state, double *unused, double *out_5980217560048262222);
void car_h_28(double *state, double *unused, double *out_6580684121977939105);
void car_H_28(double *state, double *unused, double *out_897818542978731648);
void car_h_31(double *state, double *unused, double *out_5794076051336623034);
void car_H_31(double *state, double *unused, double *out_1416058163880786289);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}