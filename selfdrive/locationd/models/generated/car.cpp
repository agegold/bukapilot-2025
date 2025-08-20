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
void err_fun(double *nom_x, double *delta_x, double *out_8269961610171249386) {
   out_8269961610171249386[0] = delta_x[0] + nom_x[0];
   out_8269961610171249386[1] = delta_x[1] + nom_x[1];
   out_8269961610171249386[2] = delta_x[2] + nom_x[2];
   out_8269961610171249386[3] = delta_x[3] + nom_x[3];
   out_8269961610171249386[4] = delta_x[4] + nom_x[4];
   out_8269961610171249386[5] = delta_x[5] + nom_x[5];
   out_8269961610171249386[6] = delta_x[6] + nom_x[6];
   out_8269961610171249386[7] = delta_x[7] + nom_x[7];
   out_8269961610171249386[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2224385476887686460) {
   out_2224385476887686460[0] = -nom_x[0] + true_x[0];
   out_2224385476887686460[1] = -nom_x[1] + true_x[1];
   out_2224385476887686460[2] = -nom_x[2] + true_x[2];
   out_2224385476887686460[3] = -nom_x[3] + true_x[3];
   out_2224385476887686460[4] = -nom_x[4] + true_x[4];
   out_2224385476887686460[5] = -nom_x[5] + true_x[5];
   out_2224385476887686460[6] = -nom_x[6] + true_x[6];
   out_2224385476887686460[7] = -nom_x[7] + true_x[7];
   out_2224385476887686460[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4022147246895696966) {
   out_4022147246895696966[0] = 1.0;
   out_4022147246895696966[1] = 0.0;
   out_4022147246895696966[2] = 0.0;
   out_4022147246895696966[3] = 0.0;
   out_4022147246895696966[4] = 0.0;
   out_4022147246895696966[5] = 0.0;
   out_4022147246895696966[6] = 0.0;
   out_4022147246895696966[7] = 0.0;
   out_4022147246895696966[8] = 0.0;
   out_4022147246895696966[9] = 0.0;
   out_4022147246895696966[10] = 1.0;
   out_4022147246895696966[11] = 0.0;
   out_4022147246895696966[12] = 0.0;
   out_4022147246895696966[13] = 0.0;
   out_4022147246895696966[14] = 0.0;
   out_4022147246895696966[15] = 0.0;
   out_4022147246895696966[16] = 0.0;
   out_4022147246895696966[17] = 0.0;
   out_4022147246895696966[18] = 0.0;
   out_4022147246895696966[19] = 0.0;
   out_4022147246895696966[20] = 1.0;
   out_4022147246895696966[21] = 0.0;
   out_4022147246895696966[22] = 0.0;
   out_4022147246895696966[23] = 0.0;
   out_4022147246895696966[24] = 0.0;
   out_4022147246895696966[25] = 0.0;
   out_4022147246895696966[26] = 0.0;
   out_4022147246895696966[27] = 0.0;
   out_4022147246895696966[28] = 0.0;
   out_4022147246895696966[29] = 0.0;
   out_4022147246895696966[30] = 1.0;
   out_4022147246895696966[31] = 0.0;
   out_4022147246895696966[32] = 0.0;
   out_4022147246895696966[33] = 0.0;
   out_4022147246895696966[34] = 0.0;
   out_4022147246895696966[35] = 0.0;
   out_4022147246895696966[36] = 0.0;
   out_4022147246895696966[37] = 0.0;
   out_4022147246895696966[38] = 0.0;
   out_4022147246895696966[39] = 0.0;
   out_4022147246895696966[40] = 1.0;
   out_4022147246895696966[41] = 0.0;
   out_4022147246895696966[42] = 0.0;
   out_4022147246895696966[43] = 0.0;
   out_4022147246895696966[44] = 0.0;
   out_4022147246895696966[45] = 0.0;
   out_4022147246895696966[46] = 0.0;
   out_4022147246895696966[47] = 0.0;
   out_4022147246895696966[48] = 0.0;
   out_4022147246895696966[49] = 0.0;
   out_4022147246895696966[50] = 1.0;
   out_4022147246895696966[51] = 0.0;
   out_4022147246895696966[52] = 0.0;
   out_4022147246895696966[53] = 0.0;
   out_4022147246895696966[54] = 0.0;
   out_4022147246895696966[55] = 0.0;
   out_4022147246895696966[56] = 0.0;
   out_4022147246895696966[57] = 0.0;
   out_4022147246895696966[58] = 0.0;
   out_4022147246895696966[59] = 0.0;
   out_4022147246895696966[60] = 1.0;
   out_4022147246895696966[61] = 0.0;
   out_4022147246895696966[62] = 0.0;
   out_4022147246895696966[63] = 0.0;
   out_4022147246895696966[64] = 0.0;
   out_4022147246895696966[65] = 0.0;
   out_4022147246895696966[66] = 0.0;
   out_4022147246895696966[67] = 0.0;
   out_4022147246895696966[68] = 0.0;
   out_4022147246895696966[69] = 0.0;
   out_4022147246895696966[70] = 1.0;
   out_4022147246895696966[71] = 0.0;
   out_4022147246895696966[72] = 0.0;
   out_4022147246895696966[73] = 0.0;
   out_4022147246895696966[74] = 0.0;
   out_4022147246895696966[75] = 0.0;
   out_4022147246895696966[76] = 0.0;
   out_4022147246895696966[77] = 0.0;
   out_4022147246895696966[78] = 0.0;
   out_4022147246895696966[79] = 0.0;
   out_4022147246895696966[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6384510303045167306) {
   out_6384510303045167306[0] = state[0];
   out_6384510303045167306[1] = state[1];
   out_6384510303045167306[2] = state[2];
   out_6384510303045167306[3] = state[3];
   out_6384510303045167306[4] = state[4];
   out_6384510303045167306[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6384510303045167306[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6384510303045167306[7] = state[7];
   out_6384510303045167306[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8622433723209998390) {
   out_8622433723209998390[0] = 1;
   out_8622433723209998390[1] = 0;
   out_8622433723209998390[2] = 0;
   out_8622433723209998390[3] = 0;
   out_8622433723209998390[4] = 0;
   out_8622433723209998390[5] = 0;
   out_8622433723209998390[6] = 0;
   out_8622433723209998390[7] = 0;
   out_8622433723209998390[8] = 0;
   out_8622433723209998390[9] = 0;
   out_8622433723209998390[10] = 1;
   out_8622433723209998390[11] = 0;
   out_8622433723209998390[12] = 0;
   out_8622433723209998390[13] = 0;
   out_8622433723209998390[14] = 0;
   out_8622433723209998390[15] = 0;
   out_8622433723209998390[16] = 0;
   out_8622433723209998390[17] = 0;
   out_8622433723209998390[18] = 0;
   out_8622433723209998390[19] = 0;
   out_8622433723209998390[20] = 1;
   out_8622433723209998390[21] = 0;
   out_8622433723209998390[22] = 0;
   out_8622433723209998390[23] = 0;
   out_8622433723209998390[24] = 0;
   out_8622433723209998390[25] = 0;
   out_8622433723209998390[26] = 0;
   out_8622433723209998390[27] = 0;
   out_8622433723209998390[28] = 0;
   out_8622433723209998390[29] = 0;
   out_8622433723209998390[30] = 1;
   out_8622433723209998390[31] = 0;
   out_8622433723209998390[32] = 0;
   out_8622433723209998390[33] = 0;
   out_8622433723209998390[34] = 0;
   out_8622433723209998390[35] = 0;
   out_8622433723209998390[36] = 0;
   out_8622433723209998390[37] = 0;
   out_8622433723209998390[38] = 0;
   out_8622433723209998390[39] = 0;
   out_8622433723209998390[40] = 1;
   out_8622433723209998390[41] = 0;
   out_8622433723209998390[42] = 0;
   out_8622433723209998390[43] = 0;
   out_8622433723209998390[44] = 0;
   out_8622433723209998390[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8622433723209998390[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8622433723209998390[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8622433723209998390[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8622433723209998390[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8622433723209998390[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8622433723209998390[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8622433723209998390[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8622433723209998390[53] = -9.8000000000000007*dt;
   out_8622433723209998390[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8622433723209998390[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8622433723209998390[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8622433723209998390[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8622433723209998390[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8622433723209998390[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8622433723209998390[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8622433723209998390[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8622433723209998390[62] = 0;
   out_8622433723209998390[63] = 0;
   out_8622433723209998390[64] = 0;
   out_8622433723209998390[65] = 0;
   out_8622433723209998390[66] = 0;
   out_8622433723209998390[67] = 0;
   out_8622433723209998390[68] = 0;
   out_8622433723209998390[69] = 0;
   out_8622433723209998390[70] = 1;
   out_8622433723209998390[71] = 0;
   out_8622433723209998390[72] = 0;
   out_8622433723209998390[73] = 0;
   out_8622433723209998390[74] = 0;
   out_8622433723209998390[75] = 0;
   out_8622433723209998390[76] = 0;
   out_8622433723209998390[77] = 0;
   out_8622433723209998390[78] = 0;
   out_8622433723209998390[79] = 0;
   out_8622433723209998390[80] = 1;
}
void h_25(double *state, double *unused, double *out_325406975583737227) {
   out_325406975583737227[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7545127896885188643) {
   out_7545127896885188643[0] = 0;
   out_7545127896885188643[1] = 0;
   out_7545127896885188643[2] = 0;
   out_7545127896885188643[3] = 0;
   out_7545127896885188643[4] = 0;
   out_7545127896885188643[5] = 0;
   out_7545127896885188643[6] = 1;
   out_7545127896885188643[7] = 0;
   out_7545127896885188643[8] = 0;
}
void h_24(double *state, double *unused, double *out_8037109127115793444) {
   out_8037109127115793444[0] = state[4];
   out_8037109127115793444[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7343690578022039837) {
   out_7343690578022039837[0] = 0;
   out_7343690578022039837[1] = 0;
   out_7343690578022039837[2] = 0;
   out_7343690578022039837[3] = 0;
   out_7343690578022039837[4] = 1;
   out_7343690578022039837[5] = 0;
   out_7343690578022039837[6] = 0;
   out_7343690578022039837[7] = 0;
   out_7343690578022039837[8] = 0;
   out_7343690578022039837[9] = 0;
   out_7343690578022039837[10] = 0;
   out_7343690578022039837[11] = 0;
   out_7343690578022039837[12] = 0;
   out_7343690578022039837[13] = 0;
   out_7343690578022039837[14] = 1;
   out_7343690578022039837[15] = 0;
   out_7343690578022039837[16] = 0;
   out_7343690578022039837[17] = 0;
}
void h_30(double *state, double *unused, double *out_8088672232404409668) {
   out_8088672232404409668[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7415788949741948573) {
   out_7415788949741948573[0] = 0;
   out_7415788949741948573[1] = 0;
   out_7415788949741948573[2] = 0;
   out_7415788949741948573[3] = 0;
   out_7415788949741948573[4] = 1;
   out_7415788949741948573[5] = 0;
   out_7415788949741948573[6] = 0;
   out_7415788949741948573[7] = 0;
   out_7415788949741948573[8] = 0;
}
void h_26(double *state, double *unused, double *out_7145162379502747233) {
   out_7145162379502747233[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3803624578011132419) {
   out_3803624578011132419[0] = 0;
   out_3803624578011132419[1] = 0;
   out_3803624578011132419[2] = 0;
   out_3803624578011132419[3] = 0;
   out_3803624578011132419[4] = 0;
   out_3803624578011132419[5] = 0;
   out_3803624578011132419[6] = 0;
   out_3803624578011132419[7] = 1;
   out_3803624578011132419[8] = 0;
}
void h_27(double *state, double *unused, double *out_3362193027028069912) {
   out_3362193027028069912[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5241025637941523662) {
   out_5241025637941523662[0] = 0;
   out_5241025637941523662[1] = 0;
   out_5241025637941523662[2] = 0;
   out_5241025637941523662[3] = 1;
   out_5241025637941523662[4] = 0;
   out_5241025637941523662[5] = 0;
   out_5241025637941523662[6] = 0;
   out_5241025637941523662[7] = 0;
   out_5241025637941523662[8] = 0;
}
void h_29(double *state, double *unused, double *out_3086998964743564023) {
   out_3086998964743564023[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3527662911071972629) {
   out_3527662911071972629[0] = 0;
   out_3527662911071972629[1] = 1;
   out_3527662911071972629[2] = 0;
   out_3527662911071972629[3] = 0;
   out_3527662911071972629[4] = 0;
   out_3527662911071972629[5] = 0;
   out_3527662911071972629[6] = 0;
   out_3527662911071972629[7] = 0;
   out_3527662911071972629[8] = 0;
}
void h_28(double *state, double *unused, double *out_5966598347836767563) {
   out_5966598347836767563[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5491293182637298880) {
   out_5491293182637298880[0] = 1;
   out_5491293182637298880[1] = 0;
   out_5491293182637298880[2] = 0;
   out_5491293182637298880[3] = 0;
   out_5491293182637298880[4] = 0;
   out_5491293182637298880[5] = 0;
   out_5491293182637298880[6] = 0;
   out_5491293182637298880[7] = 0;
   out_5491293182637298880[8] = 0;
}
void h_31(double *state, double *unused, double *out_8206679626337786412) {
   out_8206679626337786412[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7575773858762149071) {
   out_7575773858762149071[0] = 0;
   out_7575773858762149071[1] = 0;
   out_7575773858762149071[2] = 0;
   out_7575773858762149071[3] = 0;
   out_7575773858762149071[4] = 0;
   out_7575773858762149071[5] = 0;
   out_7575773858762149071[6] = 0;
   out_7575773858762149071[7] = 0;
   out_7575773858762149071[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8269961610171249386) {
  err_fun(nom_x, delta_x, out_8269961610171249386);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2224385476887686460) {
  inv_err_fun(nom_x, true_x, out_2224385476887686460);
}
void car_H_mod_fun(double *state, double *out_4022147246895696966) {
  H_mod_fun(state, out_4022147246895696966);
}
void car_f_fun(double *state, double dt, double *out_6384510303045167306) {
  f_fun(state,  dt, out_6384510303045167306);
}
void car_F_fun(double *state, double dt, double *out_8622433723209998390) {
  F_fun(state,  dt, out_8622433723209998390);
}
void car_h_25(double *state, double *unused, double *out_325406975583737227) {
  h_25(state, unused, out_325406975583737227);
}
void car_H_25(double *state, double *unused, double *out_7545127896885188643) {
  H_25(state, unused, out_7545127896885188643);
}
void car_h_24(double *state, double *unused, double *out_8037109127115793444) {
  h_24(state, unused, out_8037109127115793444);
}
void car_H_24(double *state, double *unused, double *out_7343690578022039837) {
  H_24(state, unused, out_7343690578022039837);
}
void car_h_30(double *state, double *unused, double *out_8088672232404409668) {
  h_30(state, unused, out_8088672232404409668);
}
void car_H_30(double *state, double *unused, double *out_7415788949741948573) {
  H_30(state, unused, out_7415788949741948573);
}
void car_h_26(double *state, double *unused, double *out_7145162379502747233) {
  h_26(state, unused, out_7145162379502747233);
}
void car_H_26(double *state, double *unused, double *out_3803624578011132419) {
  H_26(state, unused, out_3803624578011132419);
}
void car_h_27(double *state, double *unused, double *out_3362193027028069912) {
  h_27(state, unused, out_3362193027028069912);
}
void car_H_27(double *state, double *unused, double *out_5241025637941523662) {
  H_27(state, unused, out_5241025637941523662);
}
void car_h_29(double *state, double *unused, double *out_3086998964743564023) {
  h_29(state, unused, out_3086998964743564023);
}
void car_H_29(double *state, double *unused, double *out_3527662911071972629) {
  H_29(state, unused, out_3527662911071972629);
}
void car_h_28(double *state, double *unused, double *out_5966598347836767563) {
  h_28(state, unused, out_5966598347836767563);
}
void car_H_28(double *state, double *unused, double *out_5491293182637298880) {
  H_28(state, unused, out_5491293182637298880);
}
void car_h_31(double *state, double *unused, double *out_8206679626337786412) {
  h_31(state, unused, out_8206679626337786412);
}
void car_H_31(double *state, double *unused, double *out_7575773858762149071) {
  H_31(state, unused, out_7575773858762149071);
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
