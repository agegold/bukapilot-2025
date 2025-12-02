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
void live_H(double *in_vec, double *out_5723885137734014121);
void live_err_fun(double *nom_x, double *delta_x, double *out_5545516428937260050);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_8664808436010373796);
void live_H_mod_fun(double *state, double *out_1031899262099390361);
void live_f_fun(double *state, double dt, double *out_601746838270869279);
void live_F_fun(double *state, double dt, double *out_6171857983899186150);
void live_h_4(double *state, double *unused, double *out_800349416285792049);
void live_H_4(double *state, double *unused, double *out_2482650068203401014);
void live_h_9(double *state, double *unused, double *out_994525566750922563);
void live_H_9(double *state, double *unused, double *out_8676875070241703132);
void live_h_10(double *state, double *unused, double *out_695841039461152309);
void live_H_10(double *state, double *unused, double *out_828588151538649878);
void live_h_12(double *state, double *unused, double *out_1612060503176966267);
void live_H_12(double *state, double *unused, double *out_3898608308839331982);
void live_h_35(double *state, double *unused, double *out_5957646311072892252);
void live_H_35(double *state, double *unused, double *out_5551402659498686401);
void live_h_32(double *state, double *unused, double *out_5120231836622785031);
void live_H_32(double *state, double *unused, double *out_249901712708926157);
void live_h_13(double *state, double *unused, double *out_8539454809719564823);
void live_H_13(double *state, double *unused, double *out_2139299151445728959);
void live_h_14(double *state, double *unused, double *out_994525566750922563);
void live_H_14(double *state, double *unused, double *out_8676875070241703132);
void live_h_33(double *state, double *unused, double *out_941630051644720418);
void live_H_33(double *state, double *unused, double *out_2400845654859828797);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}