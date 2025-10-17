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
void live_H(double *in_vec, double *out_8904166353191185885);
void live_err_fun(double *nom_x, double *delta_x, double *out_1011713181312369110);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_1196583877922977899);
void live_H_mod_fun(double *state, double *out_7512789581302767909);
void live_f_fun(double *state, double dt, double *out_3560101802389077282);
void live_F_fun(double *state, double dt, double *out_6415937311201616471);
void live_h_4(double *state, double *unused, double *out_5330779922686846);
void live_H_4(double *state, double *unused, double *out_8525444517552465570);
void live_h_9(double *state, double *unused, double *out_2064364609741564434);
void live_H_9(double *state, double *unused, double *out_2634080620892638576);
void live_h_10(double *state, double *unused, double *out_4187753454365742622);
void live_H_10(double *state, double *unused, double *out_1988072022289796748);
void live_h_12(double *state, double *unused, double *out_6481724408575628192);
void live_H_12(double *state, double *unused, double *out_2144186140509732574);
void live_h_35(double *state, double *unused, double *out_6483664676329705585);
void live_H_35(double *state, double *unused, double *out_6554637498784478670);
void live_h_32(double *state, double *unused, double *out_2379174069210412822);
void live_H_32(double *state, double *unused, double *out_7673407337253163876);
void live_h_13(double *state, double *unused, double *out_6321610508299334293);
void live_H_13(double *state, double *unused, double *out_1098806285813797403);
void live_h_14(double *state, double *unused, double *out_2064364609741564434);
void live_H_14(double *state, double *unused, double *out_2634080620892638576);
void live_h_33(double *state, double *unused, double *out_6253687100922534864);
void live_H_33(double *state, double *unused, double *out_3641948794489235759);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}