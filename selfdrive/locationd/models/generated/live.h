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
void live_H(double *in_vec, double *out_4686864802681534011);
void live_err_fun(double *nom_x, double *delta_x, double *out_636638684531771063);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_5933106571760096115);
void live_H_mod_fun(double *state, double *out_107995409202040434);
void live_f_fun(double *state, double dt, double *out_2735203211390651810);
void live_F_fun(double *state, double dt, double *out_4276166217360853287);
void live_h_4(double *state, double *unused, double *out_8746811544028395078);
void live_H_4(double *state, double *unused, double *out_5919520572898513639);
void live_h_9(double *state, double *unused, double *out_3220897894620667081);
void live_H_9(double *state, double *unused, double *out_5240004565546590507);
void live_h_10(double *state, double *unused, double *out_2243040785287683851);
void live_H_10(double *state, double *unused, double *out_8434028218770632004);
void live_h_12(double *state, double *unused, double *out_8079414643370896273);
void live_H_12(double *state, double *unused, double *out_7507767092779076182);
void live_h_35(double *state, double *unused, double *out_6775447782930478556);
void live_H_35(double *state, double *unused, double *out_9160561443438430601);
void live_h_32(double *state, double *unused, double *out_6757310240011589258);
void live_H_32(double *state, double *unused, double *out_6455536930536680664);
void live_h_13(double *state, double *unused, double *out_8600587280443344754);
void live_H_13(double *state, double *unused, double *out_344100136660917512);
void live_h_14(double *state, double *unused, double *out_3220897894620667081);
void live_H_14(double *state, double *unused, double *out_5240004565546590507);
void live_h_33(double *state, double *unused, double *out_918653185062225195);
void live_H_33(double *state, double *unused, double *out_6010004438799572997);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}