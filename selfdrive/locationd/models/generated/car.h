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
void car_err_fun(double *nom_x, double *delta_x, double *out_92257903788656195);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6348947559386218661);
void car_H_mod_fun(double *state, double *out_765748846552297560);
void car_f_fun(double *state, double dt, double *out_3529799145864124788);
void car_F_fun(double *state, double dt, double *out_464404314141930947);
void car_h_25(double *state, double *unused, double *out_6669822956507434931);
void car_H_25(double *state, double *unused, double *out_5669440671736962400);
void car_h_24(double *state, double *unused, double *out_8931707117996980969);
void car_H_24(double *state, double *unused, double *out_6201731595381071115);
void car_h_30(double *state, double *unused, double *out_9042300799873417739);
void car_H_30(double *state, double *unused, double *out_5860613060480972461);
void car_h_26(double *state, double *unused, double *out_6696533725587446709);
void car_H_26(double *state, double *unused, double *out_8973966641497763001);
void car_h_27(double *state, double *unused, double *out_7837566757583576668);
void car_H_27(double *state, double *unused, double *out_8035376372281397372);
void car_h_29(double *state, double *unused, double *out_1392955626562083397);
void car_H_29(double *state, double *unused, double *out_8698004974558603211);
void car_h_28(double *state, double *unused, double *out_2611659541748251721);
void car_H_28(double *state, double *unused, double *out_3615605957489072637);
void car_h_31(double *state, double *unused, double *out_5908915101777089153);
void car_H_31(double *state, double *unused, double *out_5700628151460771963);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}