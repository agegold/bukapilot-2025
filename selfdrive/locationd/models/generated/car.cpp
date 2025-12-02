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
void err_fun(double *nom_x, double *delta_x, double *out_633373506833746237) {
   out_633373506833746237[0] = delta_x[0] + nom_x[0];
   out_633373506833746237[1] = delta_x[1] + nom_x[1];
   out_633373506833746237[2] = delta_x[2] + nom_x[2];
   out_633373506833746237[3] = delta_x[3] + nom_x[3];
   out_633373506833746237[4] = delta_x[4] + nom_x[4];
   out_633373506833746237[5] = delta_x[5] + nom_x[5];
   out_633373506833746237[6] = delta_x[6] + nom_x[6];
   out_633373506833746237[7] = delta_x[7] + nom_x[7];
   out_633373506833746237[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7027051672422316378) {
   out_7027051672422316378[0] = -nom_x[0] + true_x[0];
   out_7027051672422316378[1] = -nom_x[1] + true_x[1];
   out_7027051672422316378[2] = -nom_x[2] + true_x[2];
   out_7027051672422316378[3] = -nom_x[3] + true_x[3];
   out_7027051672422316378[4] = -nom_x[4] + true_x[4];
   out_7027051672422316378[5] = -nom_x[5] + true_x[5];
   out_7027051672422316378[6] = -nom_x[6] + true_x[6];
   out_7027051672422316378[7] = -nom_x[7] + true_x[7];
   out_7027051672422316378[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7746484100154490520) {
   out_7746484100154490520[0] = 1.0;
   out_7746484100154490520[1] = 0.0;
   out_7746484100154490520[2] = 0.0;
   out_7746484100154490520[3] = 0.0;
   out_7746484100154490520[4] = 0.0;
   out_7746484100154490520[5] = 0.0;
   out_7746484100154490520[6] = 0.0;
   out_7746484100154490520[7] = 0.0;
   out_7746484100154490520[8] = 0.0;
   out_7746484100154490520[9] = 0.0;
   out_7746484100154490520[10] = 1.0;
   out_7746484100154490520[11] = 0.0;
   out_7746484100154490520[12] = 0.0;
   out_7746484100154490520[13] = 0.0;
   out_7746484100154490520[14] = 0.0;
   out_7746484100154490520[15] = 0.0;
   out_7746484100154490520[16] = 0.0;
   out_7746484100154490520[17] = 0.0;
   out_7746484100154490520[18] = 0.0;
   out_7746484100154490520[19] = 0.0;
   out_7746484100154490520[20] = 1.0;
   out_7746484100154490520[21] = 0.0;
   out_7746484100154490520[22] = 0.0;
   out_7746484100154490520[23] = 0.0;
   out_7746484100154490520[24] = 0.0;
   out_7746484100154490520[25] = 0.0;
   out_7746484100154490520[26] = 0.0;
   out_7746484100154490520[27] = 0.0;
   out_7746484100154490520[28] = 0.0;
   out_7746484100154490520[29] = 0.0;
   out_7746484100154490520[30] = 1.0;
   out_7746484100154490520[31] = 0.0;
   out_7746484100154490520[32] = 0.0;
   out_7746484100154490520[33] = 0.0;
   out_7746484100154490520[34] = 0.0;
   out_7746484100154490520[35] = 0.0;
   out_7746484100154490520[36] = 0.0;
   out_7746484100154490520[37] = 0.0;
   out_7746484100154490520[38] = 0.0;
   out_7746484100154490520[39] = 0.0;
   out_7746484100154490520[40] = 1.0;
   out_7746484100154490520[41] = 0.0;
   out_7746484100154490520[42] = 0.0;
   out_7746484100154490520[43] = 0.0;
   out_7746484100154490520[44] = 0.0;
   out_7746484100154490520[45] = 0.0;
   out_7746484100154490520[46] = 0.0;
   out_7746484100154490520[47] = 0.0;
   out_7746484100154490520[48] = 0.0;
   out_7746484100154490520[49] = 0.0;
   out_7746484100154490520[50] = 1.0;
   out_7746484100154490520[51] = 0.0;
   out_7746484100154490520[52] = 0.0;
   out_7746484100154490520[53] = 0.0;
   out_7746484100154490520[54] = 0.0;
   out_7746484100154490520[55] = 0.0;
   out_7746484100154490520[56] = 0.0;
   out_7746484100154490520[57] = 0.0;
   out_7746484100154490520[58] = 0.0;
   out_7746484100154490520[59] = 0.0;
   out_7746484100154490520[60] = 1.0;
   out_7746484100154490520[61] = 0.0;
   out_7746484100154490520[62] = 0.0;
   out_7746484100154490520[63] = 0.0;
   out_7746484100154490520[64] = 0.0;
   out_7746484100154490520[65] = 0.0;
   out_7746484100154490520[66] = 0.0;
   out_7746484100154490520[67] = 0.0;
   out_7746484100154490520[68] = 0.0;
   out_7746484100154490520[69] = 0.0;
   out_7746484100154490520[70] = 1.0;
   out_7746484100154490520[71] = 0.0;
   out_7746484100154490520[72] = 0.0;
   out_7746484100154490520[73] = 0.0;
   out_7746484100154490520[74] = 0.0;
   out_7746484100154490520[75] = 0.0;
   out_7746484100154490520[76] = 0.0;
   out_7746484100154490520[77] = 0.0;
   out_7746484100154490520[78] = 0.0;
   out_7746484100154490520[79] = 0.0;
   out_7746484100154490520[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_23274275379461392) {
   out_23274275379461392[0] = state[0];
   out_23274275379461392[1] = state[1];
   out_23274275379461392[2] = state[2];
   out_23274275379461392[3] = state[3];
   out_23274275379461392[4] = state[4];
   out_23274275379461392[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_23274275379461392[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_23274275379461392[7] = state[7];
   out_23274275379461392[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7589757881269145047) {
   out_7589757881269145047[0] = 1;
   out_7589757881269145047[1] = 0;
   out_7589757881269145047[2] = 0;
   out_7589757881269145047[3] = 0;
   out_7589757881269145047[4] = 0;
   out_7589757881269145047[5] = 0;
   out_7589757881269145047[6] = 0;
   out_7589757881269145047[7] = 0;
   out_7589757881269145047[8] = 0;
   out_7589757881269145047[9] = 0;
   out_7589757881269145047[10] = 1;
   out_7589757881269145047[11] = 0;
   out_7589757881269145047[12] = 0;
   out_7589757881269145047[13] = 0;
   out_7589757881269145047[14] = 0;
   out_7589757881269145047[15] = 0;
   out_7589757881269145047[16] = 0;
   out_7589757881269145047[17] = 0;
   out_7589757881269145047[18] = 0;
   out_7589757881269145047[19] = 0;
   out_7589757881269145047[20] = 1;
   out_7589757881269145047[21] = 0;
   out_7589757881269145047[22] = 0;
   out_7589757881269145047[23] = 0;
   out_7589757881269145047[24] = 0;
   out_7589757881269145047[25] = 0;
   out_7589757881269145047[26] = 0;
   out_7589757881269145047[27] = 0;
   out_7589757881269145047[28] = 0;
   out_7589757881269145047[29] = 0;
   out_7589757881269145047[30] = 1;
   out_7589757881269145047[31] = 0;
   out_7589757881269145047[32] = 0;
   out_7589757881269145047[33] = 0;
   out_7589757881269145047[34] = 0;
   out_7589757881269145047[35] = 0;
   out_7589757881269145047[36] = 0;
   out_7589757881269145047[37] = 0;
   out_7589757881269145047[38] = 0;
   out_7589757881269145047[39] = 0;
   out_7589757881269145047[40] = 1;
   out_7589757881269145047[41] = 0;
   out_7589757881269145047[42] = 0;
   out_7589757881269145047[43] = 0;
   out_7589757881269145047[44] = 0;
   out_7589757881269145047[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7589757881269145047[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7589757881269145047[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7589757881269145047[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7589757881269145047[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7589757881269145047[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7589757881269145047[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7589757881269145047[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7589757881269145047[53] = -9.8000000000000007*dt;
   out_7589757881269145047[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7589757881269145047[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7589757881269145047[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7589757881269145047[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7589757881269145047[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7589757881269145047[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7589757881269145047[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7589757881269145047[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7589757881269145047[62] = 0;
   out_7589757881269145047[63] = 0;
   out_7589757881269145047[64] = 0;
   out_7589757881269145047[65] = 0;
   out_7589757881269145047[66] = 0;
   out_7589757881269145047[67] = 0;
   out_7589757881269145047[68] = 0;
   out_7589757881269145047[69] = 0;
   out_7589757881269145047[70] = 1;
   out_7589757881269145047[71] = 0;
   out_7589757881269145047[72] = 0;
   out_7589757881269145047[73] = 0;
   out_7589757881269145047[74] = 0;
   out_7589757881269145047[75] = 0;
   out_7589757881269145047[76] = 0;
   out_7589757881269145047[77] = 0;
   out_7589757881269145047[78] = 0;
   out_7589757881269145047[79] = 0;
   out_7589757881269145047[80] = 1;
}
void h_25(double *state, double *unused, double *out_7885764047385617391) {
   out_7885764047385617391[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1446704125757746717) {
   out_1446704125757746717[0] = 0;
   out_1446704125757746717[1] = 0;
   out_1446704125757746717[2] = 0;
   out_1446704125757746717[3] = 0;
   out_1446704125757746717[4] = 0;
   out_1446704125757746717[5] = 0;
   out_1446704125757746717[6] = 1;
   out_1446704125757746717[7] = 0;
   out_1446704125757746717[8] = 0;
}
void h_24(double *state, double *unused, double *out_2881583653453946631) {
   out_2881583653453946631[0] = state[4];
   out_2881583653453946631[1] = state[5];
}
void H_24(double *state, double *unused, double *out_601707516974051318) {
   out_601707516974051318[0] = 0;
   out_601707516974051318[1] = 0;
   out_601707516974051318[2] = 0;
   out_601707516974051318[3] = 0;
   out_601707516974051318[4] = 1;
   out_601707516974051318[5] = 0;
   out_601707516974051318[6] = 0;
   out_601707516974051318[7] = 0;
   out_601707516974051318[8] = 0;
   out_601707516974051318[9] = 0;
   out_601707516974051318[10] = 0;
   out_601707516974051318[11] = 0;
   out_601707516974051318[12] = 0;
   out_601707516974051318[13] = 0;
   out_601707516974051318[14] = 1;
   out_601707516974051318[15] = 0;
   out_601707516974051318[16] = 0;
   out_601707516974051318[17] = 0;
}
void h_30(double *state, double *unused, double *out_5034922589772911112) {
   out_5034922589772911112[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5469986215733870038) {
   out_5469986215733870038[0] = 0;
   out_5469986215733870038[1] = 0;
   out_5469986215733870038[2] = 0;
   out_5469986215733870038[3] = 0;
   out_5469986215733870038[4] = 1;
   out_5469986215733870038[5] = 0;
   out_5469986215733870038[6] = 0;
   out_5469986215733870038[7] = 0;
   out_5469986215733870038[8] = 0;
}
void h_26(double *state, double *unused, double *out_5480592634709264249) {
   out_5480592634709264249[0] = state[7];
}
void H_26(double *state, double *unused, double *out_789850061647434813) {
   out_789850061647434813[0] = 0;
   out_789850061647434813[1] = 0;
   out_789850061647434813[2] = 0;
   out_789850061647434813[3] = 0;
   out_789850061647434813[4] = 0;
   out_789850061647434813[5] = 0;
   out_789850061647434813[6] = 0;
   out_789850061647434813[7] = 1;
   out_789850061647434813[8] = 0;
}
void h_27(double *state, double *unused, double *out_2155323206679707572) {
   out_2155323206679707572[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3295222903933445127) {
   out_3295222903933445127[0] = 0;
   out_3295222903933445127[1] = 0;
   out_3295222903933445127[2] = 0;
   out_3295222903933445127[3] = 1;
   out_3295222903933445127[4] = 0;
   out_3295222903933445127[5] = 0;
   out_3295222903933445127[6] = 0;
   out_3295222903933445127[7] = 0;
   out_3295222903933445127[8] = 0;
}
void h_29(double *state, double *unused, double *out_753358748529250604) {
   out_753358748529250604[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5980217560048262222) {
   out_5980217560048262222[0] = 0;
   out_5980217560048262222[1] = 1;
   out_5980217560048262222[2] = 0;
   out_5980217560048262222[3] = 0;
   out_5980217560048262222[4] = 0;
   out_5980217560048262222[5] = 0;
   out_5980217560048262222[6] = 0;
   out_5980217560048262222[7] = 0;
   out_5980217560048262222[8] = 0;
}
void h_28(double *state, double *unused, double *out_6580684121977939105) {
   out_6580684121977939105[0] = state[0];
}
void H_28(double *state, double *unused, double *out_897818542978731648) {
   out_897818542978731648[0] = 1;
   out_897818542978731648[1] = 0;
   out_897818542978731648[2] = 0;
   out_897818542978731648[3] = 0;
   out_897818542978731648[4] = 0;
   out_897818542978731648[5] = 0;
   out_897818542978731648[6] = 0;
   out_897818542978731648[7] = 0;
   out_897818542978731648[8] = 0;
}
void h_31(double *state, double *unused, double *out_5794076051336623034) {
   out_5794076051336623034[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1416058163880786289) {
   out_1416058163880786289[0] = 0;
   out_1416058163880786289[1] = 0;
   out_1416058163880786289[2] = 0;
   out_1416058163880786289[3] = 0;
   out_1416058163880786289[4] = 0;
   out_1416058163880786289[5] = 0;
   out_1416058163880786289[6] = 0;
   out_1416058163880786289[7] = 0;
   out_1416058163880786289[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_633373506833746237) {
  err_fun(nom_x, delta_x, out_633373506833746237);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7027051672422316378) {
  inv_err_fun(nom_x, true_x, out_7027051672422316378);
}
void car_H_mod_fun(double *state, double *out_7746484100154490520) {
  H_mod_fun(state, out_7746484100154490520);
}
void car_f_fun(double *state, double dt, double *out_23274275379461392) {
  f_fun(state,  dt, out_23274275379461392);
}
void car_F_fun(double *state, double dt, double *out_7589757881269145047) {
  F_fun(state,  dt, out_7589757881269145047);
}
void car_h_25(double *state, double *unused, double *out_7885764047385617391) {
  h_25(state, unused, out_7885764047385617391);
}
void car_H_25(double *state, double *unused, double *out_1446704125757746717) {
  H_25(state, unused, out_1446704125757746717);
}
void car_h_24(double *state, double *unused, double *out_2881583653453946631) {
  h_24(state, unused, out_2881583653453946631);
}
void car_H_24(double *state, double *unused, double *out_601707516974051318) {
  H_24(state, unused, out_601707516974051318);
}
void car_h_30(double *state, double *unused, double *out_5034922589772911112) {
  h_30(state, unused, out_5034922589772911112);
}
void car_H_30(double *state, double *unused, double *out_5469986215733870038) {
  H_30(state, unused, out_5469986215733870038);
}
void car_h_26(double *state, double *unused, double *out_5480592634709264249) {
  h_26(state, unused, out_5480592634709264249);
}
void car_H_26(double *state, double *unused, double *out_789850061647434813) {
  H_26(state, unused, out_789850061647434813);
}
void car_h_27(double *state, double *unused, double *out_2155323206679707572) {
  h_27(state, unused, out_2155323206679707572);
}
void car_H_27(double *state, double *unused, double *out_3295222903933445127) {
  H_27(state, unused, out_3295222903933445127);
}
void car_h_29(double *state, double *unused, double *out_753358748529250604) {
  h_29(state, unused, out_753358748529250604);
}
void car_H_29(double *state, double *unused, double *out_5980217560048262222) {
  H_29(state, unused, out_5980217560048262222);
}
void car_h_28(double *state, double *unused, double *out_6580684121977939105) {
  h_28(state, unused, out_6580684121977939105);
}
void car_H_28(double *state, double *unused, double *out_897818542978731648) {
  H_28(state, unused, out_897818542978731648);
}
void car_h_31(double *state, double *unused, double *out_5794076051336623034) {
  h_31(state, unused, out_5794076051336623034);
}
void car_H_31(double *state, double *unused, double *out_1416058163880786289) {
  H_31(state, unused, out_1416058163880786289);
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
