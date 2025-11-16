#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_5366841907483575571);
void live_err_fun(double *nom_x, double *delta_x, double *out_3687296270178721437);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_3897555735717852259);
void live_H_mod_fun(double *state, double *out_8789120384944108250);
void live_f_fun(double *state, double dt, double *out_2561011469022403888);
void live_F_fun(double *state, double dt, double *out_4398820288567042580);
void live_h_4(double *state, double *unused, double *out_3189150708892472139);
void live_H_4(double *state, double *unused, double *out_88765568143399326);
void live_h_9(double *state, double *unused, double *out_1491361123618102106);
void live_H_9(double *state, double *unused, double *out_329955214772989971);
void live_h_10(double *state, double *unused, double *out_3041369835152717088);
void live_H_10(double *state, double *unused, double *out_8069221810822936882);
void live_h_12(double *state, double *unused, double *out_8906526622869280736);
void live_H_12(double *state, double *unused, double *out_5108221976175361121);
void live_h_35(double *state, double *unused, double *out_7421612446542020888);
void live_H_35(double *state, double *unused, double *out_7853785008500374830);
void live_h_32(double *state, double *unused, double *out_155264768541608026);
void live_H_32(double *state, double *unused, double *out_8652120727876167985);
void live_h_13(double *state, double *unused, double *out_4370330703449834769);
void live_H_13(double *state, double *unused, double *out_5978729775232095694);
void live_h_14(double *state, double *unused, double *out_1491361123618102106);
void live_H_14(double *state, double *unused, double *out_329955214772989971);
void live_h_33(double *state, double *unused, double *out_7279928929202261534);
void live_H_33(double *state, double *unused, double *out_7442402060570319182);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}