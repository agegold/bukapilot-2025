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
void live_H(double *in_vec, double *out_8916027857835573622);
void live_err_fun(double *nom_x, double *delta_x, double *out_6737279551475501310);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4601009534180412750);
void live_H_mod_fun(double *state, double *out_2208866408237948591);
void live_f_fun(double *state, double dt, double *out_1487471589008722616);
void live_F_fun(double *state, double dt, double *out_7380499877901662279);
void live_h_4(double *state, double *unused, double *out_1594346727579217617);
void live_H_4(double *state, double *unused, double *out_4101537254120495657);
void live_h_9(double *state, double *unused, double *out_9199208335471572768);
void live_H_9(double *state, double *unused, double *out_7057987884324608489);
void live_h_10(double *state, double *unused, double *out_9127425986072825078);
void live_H_10(double *state, double *unused, double *out_5717492833735214824);
void live_h_12(double *state, double *unused, double *out_4979930024815781582);
void live_H_12(double *state, double *unused, double *out_2279721122922237339);
void live_h_35(double *state, double *unused, double *out_8883308242832364228);
void live_H_35(double *state, double *unused, double *out_465841909402776370);
void live_h_32(double *state, double *unused, double *out_3191736591977102565);
void live_H_32(double *state, double *unused, double *out_3875162866330330518);
void live_h_13(double *state, double *unused, double *out_3335727981914774021);
void live_H_13(double *state, double *unused, double *out_5543749575064104696);
void live_h_14(double *state, double *unused, double *out_9199208335471572768);
void live_H_14(double *state, double *unused, double *out_7057987884324608489);
void live_h_33(double *state, double *unused, double *out_6738279592511776487);
void live_H_33(double *state, double *unused, double *out_781958468942734154);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}