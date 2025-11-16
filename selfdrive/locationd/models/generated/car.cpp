#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_54115344297803870) {
   out_54115344297803870[0] = delta_x[0] + nom_x[0];
   out_54115344297803870[1] = delta_x[1] + nom_x[1];
   out_54115344297803870[2] = delta_x[2] + nom_x[2];
   out_54115344297803870[3] = delta_x[3] + nom_x[3];
   out_54115344297803870[4] = delta_x[4] + nom_x[4];
   out_54115344297803870[5] = delta_x[5] + nom_x[5];
   out_54115344297803870[6] = delta_x[6] + nom_x[6];
   out_54115344297803870[7] = delta_x[7] + nom_x[7];
   out_54115344297803870[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_486023171127865793) {
   out_486023171127865793[0] = -nom_x[0] + true_x[0];
   out_486023171127865793[1] = -nom_x[1] + true_x[1];
   out_486023171127865793[2] = -nom_x[2] + true_x[2];
   out_486023171127865793[3] = -nom_x[3] + true_x[3];
   out_486023171127865793[4] = -nom_x[4] + true_x[4];
   out_486023171127865793[5] = -nom_x[5] + true_x[5];
   out_486023171127865793[6] = -nom_x[6] + true_x[6];
   out_486023171127865793[7] = -nom_x[7] + true_x[7];
   out_486023171127865793[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_741897642024606427) {
   out_741897642024606427[0] = 1.0;
   out_741897642024606427[1] = 0.0;
   out_741897642024606427[2] = 0.0;
   out_741897642024606427[3] = 0.0;
   out_741897642024606427[4] = 0.0;
   out_741897642024606427[5] = 0.0;
   out_741897642024606427[6] = 0.0;
   out_741897642024606427[7] = 0.0;
   out_741897642024606427[8] = 0.0;
   out_741897642024606427[9] = 0.0;
   out_741897642024606427[10] = 1.0;
   out_741897642024606427[11] = 0.0;
   out_741897642024606427[12] = 0.0;
   out_741897642024606427[13] = 0.0;
   out_741897642024606427[14] = 0.0;
   out_741897642024606427[15] = 0.0;
   out_741897642024606427[16] = 0.0;
   out_741897642024606427[17] = 0.0;
   out_741897642024606427[18] = 0.0;
   out_741897642024606427[19] = 0.0;
   out_741897642024606427[20] = 1.0;
   out_741897642024606427[21] = 0.0;
   out_741897642024606427[22] = 0.0;
   out_741897642024606427[23] = 0.0;
   out_741897642024606427[24] = 0.0;
   out_741897642024606427[25] = 0.0;
   out_741897642024606427[26] = 0.0;
   out_741897642024606427[27] = 0.0;
   out_741897642024606427[28] = 0.0;
   out_741897642024606427[29] = 0.0;
   out_741897642024606427[30] = 1.0;
   out_741897642024606427[31] = 0.0;
   out_741897642024606427[32] = 0.0;
   out_741897642024606427[33] = 0.0;
   out_741897642024606427[34] = 0.0;
   out_741897642024606427[35] = 0.0;
   out_741897642024606427[36] = 0.0;
   out_741897642024606427[37] = 0.0;
   out_741897642024606427[38] = 0.0;
   out_741897642024606427[39] = 0.0;
   out_741897642024606427[40] = 1.0;
   out_741897642024606427[41] = 0.0;
   out_741897642024606427[42] = 0.0;
   out_741897642024606427[43] = 0.0;
   out_741897642024606427[44] = 0.0;
   out_741897642024606427[45] = 0.0;
   out_741897642024606427[46] = 0.0;
   out_741897642024606427[47] = 0.0;
   out_741897642024606427[48] = 0.0;
   out_741897642024606427[49] = 0.0;
   out_741897642024606427[50] = 1.0;
   out_741897642024606427[51] = 0.0;
   out_741897642024606427[52] = 0.0;
   out_741897642024606427[53] = 0.0;
   out_741897642024606427[54] = 0.0;
   out_741897642024606427[55] = 0.0;
   out_741897642024606427[56] = 0.0;
   out_741897642024606427[57] = 0.0;
   out_741897642024606427[58] = 0.0;
   out_741897642024606427[59] = 0.0;
   out_741897642024606427[60] = 1.0;
   out_741897642024606427[61] = 0.0;
   out_741897642024606427[62] = 0.0;
   out_741897642024606427[63] = 0.0;
   out_741897642024606427[64] = 0.0;
   out_741897642024606427[65] = 0.0;
   out_741897642024606427[66] = 0.0;
   out_741897642024606427[67] = 0.0;
   out_741897642024606427[68] = 0.0;
   out_741897642024606427[69] = 0.0;
   out_741897642024606427[70] = 1.0;
   out_741897642024606427[71] = 0.0;
   out_741897642024606427[72] = 0.0;
   out_741897642024606427[73] = 0.0;
   out_741897642024606427[74] = 0.0;
   out_741897642024606427[75] = 0.0;
   out_741897642024606427[76] = 0.0;
   out_741897642024606427[77] = 0.0;
   out_741897642024606427[78] = 0.0;
   out_741897642024606427[79] = 0.0;
   out_741897642024606427[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2982029055930059059) {
   out_2982029055930059059[0] = state[0];
   out_2982029055930059059[1] = state[1];
   out_2982029055930059059[2] = state[2];
   out_2982029055930059059[3] = state[3];
   out_2982029055930059059[4] = state[4];
   out_2982029055930059059[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2982029055930059059[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2982029055930059059[7] = state[7];
   out_2982029055930059059[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6513532347961345036) {
   out_6513532347961345036[0] = 1;
   out_6513532347961345036[1] = 0;
   out_6513532347961345036[2] = 0;
   out_6513532347961345036[3] = 0;
   out_6513532347961345036[4] = 0;
   out_6513532347961345036[5] = 0;
   out_6513532347961345036[6] = 0;
   out_6513532347961345036[7] = 0;
   out_6513532347961345036[8] = 0;
   out_6513532347961345036[9] = 0;
   out_6513532347961345036[10] = 1;
   out_6513532347961345036[11] = 0;
   out_6513532347961345036[12] = 0;
   out_6513532347961345036[13] = 0;
   out_6513532347961345036[14] = 0;
   out_6513532347961345036[15] = 0;
   out_6513532347961345036[16] = 0;
   out_6513532347961345036[17] = 0;
   out_6513532347961345036[18] = 0;
   out_6513532347961345036[19] = 0;
   out_6513532347961345036[20] = 1;
   out_6513532347961345036[21] = 0;
   out_6513532347961345036[22] = 0;
   out_6513532347961345036[23] = 0;
   out_6513532347961345036[24] = 0;
   out_6513532347961345036[25] = 0;
   out_6513532347961345036[26] = 0;
   out_6513532347961345036[27] = 0;
   out_6513532347961345036[28] = 0;
   out_6513532347961345036[29] = 0;
   out_6513532347961345036[30] = 1;
   out_6513532347961345036[31] = 0;
   out_6513532347961345036[32] = 0;
   out_6513532347961345036[33] = 0;
   out_6513532347961345036[34] = 0;
   out_6513532347961345036[35] = 0;
   out_6513532347961345036[36] = 0;
   out_6513532347961345036[37] = 0;
   out_6513532347961345036[38] = 0;
   out_6513532347961345036[39] = 0;
   out_6513532347961345036[40] = 1;
   out_6513532347961345036[41] = 0;
   out_6513532347961345036[42] = 0;
   out_6513532347961345036[43] = 0;
   out_6513532347961345036[44] = 0;
   out_6513532347961345036[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6513532347961345036[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6513532347961345036[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6513532347961345036[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6513532347961345036[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6513532347961345036[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6513532347961345036[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6513532347961345036[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6513532347961345036[53] = -9.8000000000000007*dt;
   out_6513532347961345036[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6513532347961345036[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6513532347961345036[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6513532347961345036[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6513532347961345036[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6513532347961345036[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6513532347961345036[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6513532347961345036[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6513532347961345036[62] = 0;
   out_6513532347961345036[63] = 0;
   out_6513532347961345036[64] = 0;
   out_6513532347961345036[65] = 0;
   out_6513532347961345036[66] = 0;
   out_6513532347961345036[67] = 0;
   out_6513532347961345036[68] = 0;
   out_6513532347961345036[69] = 0;
   out_6513532347961345036[70] = 1;
   out_6513532347961345036[71] = 0;
   out_6513532347961345036[72] = 0;
   out_6513532347961345036[73] = 0;
   out_6513532347961345036[74] = 0;
   out_6513532347961345036[75] = 0;
   out_6513532347961345036[76] = 0;
   out_6513532347961345036[77] = 0;
   out_6513532347961345036[78] = 0;
   out_6513532347961345036[79] = 0;
   out_6513532347961345036[80] = 1;
}
void h_25(double *state, double *unused, double *out_3229136396796182411) {
   out_3229136396796182411[0] = state[6];
}
void H_25(double *state, double *unused, double *out_9092266040851434872) {
   out_9092266040851434872[0] = 0;
   out_9092266040851434872[1] = 0;
   out_9092266040851434872[2] = 0;
   out_9092266040851434872[3] = 0;
   out_9092266040851434872[4] = 0;
   out_9092266040851434872[5] = 0;
   out_9092266040851434872[6] = 1;
   out_9092266040851434872[7] = 0;
   out_9092266040851434872[8] = 0;
}
void h_24(double *state, double *unused, double *out_1430429500839531180) {
   out_1430429500839531180[0] = state[4];
   out_1430429500839531180[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3280880409828657907) {
   out_3280880409828657907[0] = 0;
   out_3280880409828657907[1] = 0;
   out_3280880409828657907[2] = 0;
   out_3280880409828657907[3] = 0;
   out_3280880409828657907[4] = 1;
   out_3280880409828657907[5] = 0;
   out_3280880409828657907[6] = 0;
   out_3280880409828657907[7] = 0;
   out_3280880409828657907[8] = 0;
   out_3280880409828657907[9] = 0;
   out_3280880409828657907[10] = 0;
   out_3280880409828657907[11] = 0;
   out_3280880409828657907[12] = 0;
   out_3280880409828657907[13] = 0;
   out_3280880409828657907[14] = 1;
   out_3280880409828657907[15] = 0;
   out_3280880409828657907[16] = 0;
   out_3280880409828657907[17] = 0;
}
void h_30(double *state, double *unused, double *out_281410406440697450) {
   out_281410406440697450[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2175575699359818117) {
   out_2175575699359818117[0] = 0;
   out_2175575699359818117[1] = 0;
   out_2175575699359818117[2] = 0;
   out_2175575699359818117[3] = 0;
   out_2175575699359818117[4] = 1;
   out_2175575699359818117[5] = 0;
   out_2175575699359818117[6] = 0;
   out_2175575699359818117[7] = 0;
   out_2175575699359818117[8] = 0;
}
void h_26(double *state, double *unused, double *out_2531141696829155933) {
   out_2531141696829155933[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5787740071090634271) {
   out_5787740071090634271[0] = 0;
   out_5787740071090634271[1] = 0;
   out_5787740071090634271[2] = 0;
   out_5787740071090634271[3] = 0;
   out_5787740071090634271[4] = 0;
   out_5787740071090634271[5] = 0;
   out_5787740071090634271[6] = 0;
   out_5787740071090634271[7] = 1;
   out_5787740071090634271[8] = 0;
}
void h_27(double *state, double *unused, double *out_5833541717604880062) {
   out_5833541717604880062[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4350339011160243028) {
   out_4350339011160243028[0] = 0;
   out_4350339011160243028[1] = 0;
   out_4350339011160243028[2] = 0;
   out_4350339011160243028[3] = 1;
   out_4350339011160243028[4] = 0;
   out_4350339011160243028[5] = 0;
   out_4350339011160243028[6] = 0;
   out_4350339011160243028[7] = 0;
   out_4350339011160243028[8] = 0;
}
void h_29(double *state, double *unused, double *out_4720262861220148195) {
   out_4720262861220148195[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6063701738029794061) {
   out_6063701738029794061[0] = 0;
   out_6063701738029794061[1] = 1;
   out_6063701738029794061[2] = 0;
   out_6063701738029794061[3] = 0;
   out_6063701738029794061[4] = 0;
   out_6063701738029794061[5] = 0;
   out_6063701738029794061[6] = 0;
   out_6063701738029794061[7] = 0;
   out_6063701738029794061[8] = 0;
}
void h_28(double *state, double *unused, double *out_7209432301142177531) {
   out_7209432301142177531[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7300643318610226981) {
   out_7300643318610226981[0] = 1;
   out_7300643318610226981[1] = 0;
   out_7300643318610226981[2] = 0;
   out_7300643318610226981[3] = 0;
   out_7300643318610226981[4] = 0;
   out_7300643318610226981[5] = 0;
   out_7300643318610226981[6] = 0;
   out_7300643318610226981[7] = 0;
   out_7300643318610226981[8] = 0;
}
void h_31(double *state, double *unused, double *out_7336335026159320020) {
   out_7336335026159320020[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2015590790339617619) {
   out_2015590790339617619[0] = 0;
   out_2015590790339617619[1] = 0;
   out_2015590790339617619[2] = 0;
   out_2015590790339617619[3] = 0;
   out_2015590790339617619[4] = 0;
   out_2015590790339617619[5] = 0;
   out_2015590790339617619[6] = 0;
   out_2015590790339617619[7] = 0;
   out_2015590790339617619[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_54115344297803870) {
  err_fun(nom_x, delta_x, out_54115344297803870);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_486023171127865793) {
  inv_err_fun(nom_x, true_x, out_486023171127865793);
}
void car_H_mod_fun(double *state, double *out_741897642024606427) {
  H_mod_fun(state, out_741897642024606427);
}
void car_f_fun(double *state, double dt, double *out_2982029055930059059) {
  f_fun(state,  dt, out_2982029055930059059);
}
void car_F_fun(double *state, double dt, double *out_6513532347961345036) {
  F_fun(state,  dt, out_6513532347961345036);
}
void car_h_25(double *state, double *unused, double *out_3229136396796182411) {
  h_25(state, unused, out_3229136396796182411);
}
void car_H_25(double *state, double *unused, double *out_9092266040851434872) {
  H_25(state, unused, out_9092266040851434872);
}
void car_h_24(double *state, double *unused, double *out_1430429500839531180) {
  h_24(state, unused, out_1430429500839531180);
}
void car_H_24(double *state, double *unused, double *out_3280880409828657907) {
  H_24(state, unused, out_3280880409828657907);
}
void car_h_30(double *state, double *unused, double *out_281410406440697450) {
  h_30(state, unused, out_281410406440697450);
}
void car_H_30(double *state, double *unused, double *out_2175575699359818117) {
  H_30(state, unused, out_2175575699359818117);
}
void car_h_26(double *state, double *unused, double *out_2531141696829155933) {
  h_26(state, unused, out_2531141696829155933);
}
void car_H_26(double *state, double *unused, double *out_5787740071090634271) {
  H_26(state, unused, out_5787740071090634271);
}
void car_h_27(double *state, double *unused, double *out_5833541717604880062) {
  h_27(state, unused, out_5833541717604880062);
}
void car_H_27(double *state, double *unused, double *out_4350339011160243028) {
  H_27(state, unused, out_4350339011160243028);
}
void car_h_29(double *state, double *unused, double *out_4720262861220148195) {
  h_29(state, unused, out_4720262861220148195);
}
void car_H_29(double *state, double *unused, double *out_6063701738029794061) {
  H_29(state, unused, out_6063701738029794061);
}
void car_h_28(double *state, double *unused, double *out_7209432301142177531) {
  h_28(state, unused, out_7209432301142177531);
}
void car_H_28(double *state, double *unused, double *out_7300643318610226981) {
  H_28(state, unused, out_7300643318610226981);
}
void car_h_31(double *state, double *unused, double *out_7336335026159320020) {
  h_31(state, unused, out_7336335026159320020);
}
void car_H_31(double *state, double *unused, double *out_2015590790339617619) {
  H_31(state, unused, out_2015590790339617619);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
