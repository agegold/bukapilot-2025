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
void err_fun(double *nom_x, double *delta_x, double *out_7009082287290678410) {
   out_7009082287290678410[0] = delta_x[0] + nom_x[0];
   out_7009082287290678410[1] = delta_x[1] + nom_x[1];
   out_7009082287290678410[2] = delta_x[2] + nom_x[2];
   out_7009082287290678410[3] = delta_x[3] + nom_x[3];
   out_7009082287290678410[4] = delta_x[4] + nom_x[4];
   out_7009082287290678410[5] = delta_x[5] + nom_x[5];
   out_7009082287290678410[6] = delta_x[6] + nom_x[6];
   out_7009082287290678410[7] = delta_x[7] + nom_x[7];
   out_7009082287290678410[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6773512853317553183) {
   out_6773512853317553183[0] = -nom_x[0] + true_x[0];
   out_6773512853317553183[1] = -nom_x[1] + true_x[1];
   out_6773512853317553183[2] = -nom_x[2] + true_x[2];
   out_6773512853317553183[3] = -nom_x[3] + true_x[3];
   out_6773512853317553183[4] = -nom_x[4] + true_x[4];
   out_6773512853317553183[5] = -nom_x[5] + true_x[5];
   out_6773512853317553183[6] = -nom_x[6] + true_x[6];
   out_6773512853317553183[7] = -nom_x[7] + true_x[7];
   out_6773512853317553183[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5453048751080424150) {
   out_5453048751080424150[0] = 1.0;
   out_5453048751080424150[1] = 0.0;
   out_5453048751080424150[2] = 0.0;
   out_5453048751080424150[3] = 0.0;
   out_5453048751080424150[4] = 0.0;
   out_5453048751080424150[5] = 0.0;
   out_5453048751080424150[6] = 0.0;
   out_5453048751080424150[7] = 0.0;
   out_5453048751080424150[8] = 0.0;
   out_5453048751080424150[9] = 0.0;
   out_5453048751080424150[10] = 1.0;
   out_5453048751080424150[11] = 0.0;
   out_5453048751080424150[12] = 0.0;
   out_5453048751080424150[13] = 0.0;
   out_5453048751080424150[14] = 0.0;
   out_5453048751080424150[15] = 0.0;
   out_5453048751080424150[16] = 0.0;
   out_5453048751080424150[17] = 0.0;
   out_5453048751080424150[18] = 0.0;
   out_5453048751080424150[19] = 0.0;
   out_5453048751080424150[20] = 1.0;
   out_5453048751080424150[21] = 0.0;
   out_5453048751080424150[22] = 0.0;
   out_5453048751080424150[23] = 0.0;
   out_5453048751080424150[24] = 0.0;
   out_5453048751080424150[25] = 0.0;
   out_5453048751080424150[26] = 0.0;
   out_5453048751080424150[27] = 0.0;
   out_5453048751080424150[28] = 0.0;
   out_5453048751080424150[29] = 0.0;
   out_5453048751080424150[30] = 1.0;
   out_5453048751080424150[31] = 0.0;
   out_5453048751080424150[32] = 0.0;
   out_5453048751080424150[33] = 0.0;
   out_5453048751080424150[34] = 0.0;
   out_5453048751080424150[35] = 0.0;
   out_5453048751080424150[36] = 0.0;
   out_5453048751080424150[37] = 0.0;
   out_5453048751080424150[38] = 0.0;
   out_5453048751080424150[39] = 0.0;
   out_5453048751080424150[40] = 1.0;
   out_5453048751080424150[41] = 0.0;
   out_5453048751080424150[42] = 0.0;
   out_5453048751080424150[43] = 0.0;
   out_5453048751080424150[44] = 0.0;
   out_5453048751080424150[45] = 0.0;
   out_5453048751080424150[46] = 0.0;
   out_5453048751080424150[47] = 0.0;
   out_5453048751080424150[48] = 0.0;
   out_5453048751080424150[49] = 0.0;
   out_5453048751080424150[50] = 1.0;
   out_5453048751080424150[51] = 0.0;
   out_5453048751080424150[52] = 0.0;
   out_5453048751080424150[53] = 0.0;
   out_5453048751080424150[54] = 0.0;
   out_5453048751080424150[55] = 0.0;
   out_5453048751080424150[56] = 0.0;
   out_5453048751080424150[57] = 0.0;
   out_5453048751080424150[58] = 0.0;
   out_5453048751080424150[59] = 0.0;
   out_5453048751080424150[60] = 1.0;
   out_5453048751080424150[61] = 0.0;
   out_5453048751080424150[62] = 0.0;
   out_5453048751080424150[63] = 0.0;
   out_5453048751080424150[64] = 0.0;
   out_5453048751080424150[65] = 0.0;
   out_5453048751080424150[66] = 0.0;
   out_5453048751080424150[67] = 0.0;
   out_5453048751080424150[68] = 0.0;
   out_5453048751080424150[69] = 0.0;
   out_5453048751080424150[70] = 1.0;
   out_5453048751080424150[71] = 0.0;
   out_5453048751080424150[72] = 0.0;
   out_5453048751080424150[73] = 0.0;
   out_5453048751080424150[74] = 0.0;
   out_5453048751080424150[75] = 0.0;
   out_5453048751080424150[76] = 0.0;
   out_5453048751080424150[77] = 0.0;
   out_5453048751080424150[78] = 0.0;
   out_5453048751080424150[79] = 0.0;
   out_5453048751080424150[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2696784723507792136) {
   out_2696784723507792136[0] = state[0];
   out_2696784723507792136[1] = state[1];
   out_2696784723507792136[2] = state[2];
   out_2696784723507792136[3] = state[3];
   out_2696784723507792136[4] = state[4];
   out_2696784723507792136[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2696784723507792136[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2696784723507792136[7] = state[7];
   out_2696784723507792136[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2855698406566993747) {
   out_2855698406566993747[0] = 1;
   out_2855698406566993747[1] = 0;
   out_2855698406566993747[2] = 0;
   out_2855698406566993747[3] = 0;
   out_2855698406566993747[4] = 0;
   out_2855698406566993747[5] = 0;
   out_2855698406566993747[6] = 0;
   out_2855698406566993747[7] = 0;
   out_2855698406566993747[8] = 0;
   out_2855698406566993747[9] = 0;
   out_2855698406566993747[10] = 1;
   out_2855698406566993747[11] = 0;
   out_2855698406566993747[12] = 0;
   out_2855698406566993747[13] = 0;
   out_2855698406566993747[14] = 0;
   out_2855698406566993747[15] = 0;
   out_2855698406566993747[16] = 0;
   out_2855698406566993747[17] = 0;
   out_2855698406566993747[18] = 0;
   out_2855698406566993747[19] = 0;
   out_2855698406566993747[20] = 1;
   out_2855698406566993747[21] = 0;
   out_2855698406566993747[22] = 0;
   out_2855698406566993747[23] = 0;
   out_2855698406566993747[24] = 0;
   out_2855698406566993747[25] = 0;
   out_2855698406566993747[26] = 0;
   out_2855698406566993747[27] = 0;
   out_2855698406566993747[28] = 0;
   out_2855698406566993747[29] = 0;
   out_2855698406566993747[30] = 1;
   out_2855698406566993747[31] = 0;
   out_2855698406566993747[32] = 0;
   out_2855698406566993747[33] = 0;
   out_2855698406566993747[34] = 0;
   out_2855698406566993747[35] = 0;
   out_2855698406566993747[36] = 0;
   out_2855698406566993747[37] = 0;
   out_2855698406566993747[38] = 0;
   out_2855698406566993747[39] = 0;
   out_2855698406566993747[40] = 1;
   out_2855698406566993747[41] = 0;
   out_2855698406566993747[42] = 0;
   out_2855698406566993747[43] = 0;
   out_2855698406566993747[44] = 0;
   out_2855698406566993747[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2855698406566993747[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2855698406566993747[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2855698406566993747[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2855698406566993747[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2855698406566993747[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2855698406566993747[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2855698406566993747[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2855698406566993747[53] = -9.8000000000000007*dt;
   out_2855698406566993747[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2855698406566993747[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2855698406566993747[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2855698406566993747[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2855698406566993747[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2855698406566993747[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2855698406566993747[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2855698406566993747[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2855698406566993747[62] = 0;
   out_2855698406566993747[63] = 0;
   out_2855698406566993747[64] = 0;
   out_2855698406566993747[65] = 0;
   out_2855698406566993747[66] = 0;
   out_2855698406566993747[67] = 0;
   out_2855698406566993747[68] = 0;
   out_2855698406566993747[69] = 0;
   out_2855698406566993747[70] = 1;
   out_2855698406566993747[71] = 0;
   out_2855698406566993747[72] = 0;
   out_2855698406566993747[73] = 0;
   out_2855698406566993747[74] = 0;
   out_2855698406566993747[75] = 0;
   out_2855698406566993747[76] = 0;
   out_2855698406566993747[77] = 0;
   out_2855698406566993747[78] = 0;
   out_2855698406566993747[79] = 0;
   out_2855698406566993747[80] = 1;
}
void h_25(double *state, double *unused, double *out_4410045275916909057) {
   out_4410045275916909057[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5072357289655267661) {
   out_5072357289655267661[0] = 0;
   out_5072357289655267661[1] = 0;
   out_5072357289655267661[2] = 0;
   out_5072357289655267661[3] = 0;
   out_5072357289655267661[4] = 0;
   out_5072357289655267661[5] = 0;
   out_5072357289655267661[6] = 1;
   out_5072357289655267661[7] = 0;
   out_5072357289655267661[8] = 0;
}
void h_24(double *state, double *unused, double *out_6567175883780815729) {
   out_6567175883780815729[0] = state[4];
   out_6567175883780815729[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1514431690852944525) {
   out_1514431690852944525[0] = 0;
   out_1514431690852944525[1] = 0;
   out_1514431690852944525[2] = 0;
   out_1514431690852944525[3] = 0;
   out_1514431690852944525[4] = 1;
   out_1514431690852944525[5] = 0;
   out_1514431690852944525[6] = 0;
   out_1514431690852944525[7] = 0;
   out_1514431690852944525[8] = 0;
   out_1514431690852944525[9] = 0;
   out_1514431690852944525[10] = 0;
   out_1514431690852944525[11] = 0;
   out_1514431690852944525[12] = 0;
   out_1514431690852944525[13] = 0;
   out_1514431690852944525[14] = 1;
   out_1514431690852944525[15] = 0;
   out_1514431690852944525[16] = 0;
   out_1514431690852944525[17] = 0;
}
void h_30(double *state, double *unused, double *out_6497667489146449420) {
   out_6497667489146449420[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2554024331148019034) {
   out_2554024331148019034[0] = 0;
   out_2554024331148019034[1] = 0;
   out_2554024331148019034[2] = 0;
   out_2554024331148019034[3] = 0;
   out_2554024331148019034[4] = 1;
   out_2554024331148019034[5] = 0;
   out_2554024331148019034[6] = 0;
   out_2554024331148019034[7] = 0;
   out_2554024331148019034[8] = 0;
}
void h_26(double *state, double *unused, double *out_1142086035247273555) {
   out_1142086035247273555[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8813860608529323885) {
   out_8813860608529323885[0] = 0;
   out_8813860608529323885[1] = 0;
   out_8813860608529323885[2] = 0;
   out_8813860608529323885[3] = 0;
   out_8813860608529323885[4] = 0;
   out_8813860608529323885[5] = 0;
   out_8813860608529323885[6] = 0;
   out_8813860608529323885[7] = 1;
   out_8813860608529323885[8] = 0;
}
void h_27(double *state, double *unused, double *out_7222597379186762440) {
   out_7222597379186762440[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4728787642948443945) {
   out_4728787642948443945[0] = 0;
   out_4728787642948443945[1] = 0;
   out_4728787642948443945[2] = 0;
   out_4728787642948443945[3] = 1;
   out_4728787642948443945[4] = 0;
   out_4728787642948443945[5] = 0;
   out_4728787642948443945[6] = 0;
   out_4728787642948443945[7] = 0;
   out_4728787642948443945[8] = 0;
}
void h_29(double *state, double *unused, double *out_6947403316902256551) {
   out_6947403316902256551[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2043792986833626850) {
   out_2043792986833626850[0] = 0;
   out_2043792986833626850[1] = 1;
   out_2043792986833626850[2] = 0;
   out_2043792986833626850[3] = 0;
   out_2043792986833626850[4] = 0;
   out_2043792986833626850[5] = 0;
   out_2043792986833626850[6] = 0;
   out_2043792986833626850[7] = 0;
   out_2043792986833626850[8] = 0;
}
void h_28(double *state, double *unused, double *out_1344311891628047352) {
   out_1344311891628047352[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7126192003903157424) {
   out_7126192003903157424[0] = 1;
   out_7126192003903157424[1] = 0;
   out_7126192003903157424[2] = 0;
   out_7126192003903157424[3] = 0;
   out_7126192003903157424[4] = 0;
   out_7126192003903157424[5] = 0;
   out_7126192003903157424[6] = 0;
   out_7126192003903157424[7] = 0;
   out_7126192003903157424[8] = 0;
}
void h_31(double *state, double *unused, double *out_2585023898607921181) {
   out_2585023898607921181[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9006675362946876255) {
   out_9006675362946876255[0] = 0;
   out_9006675362946876255[1] = 0;
   out_9006675362946876255[2] = 0;
   out_9006675362946876255[3] = 0;
   out_9006675362946876255[4] = 0;
   out_9006675362946876255[5] = 0;
   out_9006675362946876255[6] = 0;
   out_9006675362946876255[7] = 0;
   out_9006675362946876255[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7009082287290678410) {
  err_fun(nom_x, delta_x, out_7009082287290678410);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6773512853317553183) {
  inv_err_fun(nom_x, true_x, out_6773512853317553183);
}
void car_H_mod_fun(double *state, double *out_5453048751080424150) {
  H_mod_fun(state, out_5453048751080424150);
}
void car_f_fun(double *state, double dt, double *out_2696784723507792136) {
  f_fun(state,  dt, out_2696784723507792136);
}
void car_F_fun(double *state, double dt, double *out_2855698406566993747) {
  F_fun(state,  dt, out_2855698406566993747);
}
void car_h_25(double *state, double *unused, double *out_4410045275916909057) {
  h_25(state, unused, out_4410045275916909057);
}
void car_H_25(double *state, double *unused, double *out_5072357289655267661) {
  H_25(state, unused, out_5072357289655267661);
}
void car_h_24(double *state, double *unused, double *out_6567175883780815729) {
  h_24(state, unused, out_6567175883780815729);
}
void car_H_24(double *state, double *unused, double *out_1514431690852944525) {
  H_24(state, unused, out_1514431690852944525);
}
void car_h_30(double *state, double *unused, double *out_6497667489146449420) {
  h_30(state, unused, out_6497667489146449420);
}
void car_H_30(double *state, double *unused, double *out_2554024331148019034) {
  H_30(state, unused, out_2554024331148019034);
}
void car_h_26(double *state, double *unused, double *out_1142086035247273555) {
  h_26(state, unused, out_1142086035247273555);
}
void car_H_26(double *state, double *unused, double *out_8813860608529323885) {
  H_26(state, unused, out_8813860608529323885);
}
void car_h_27(double *state, double *unused, double *out_7222597379186762440) {
  h_27(state, unused, out_7222597379186762440);
}
void car_H_27(double *state, double *unused, double *out_4728787642948443945) {
  H_27(state, unused, out_4728787642948443945);
}
void car_h_29(double *state, double *unused, double *out_6947403316902256551) {
  h_29(state, unused, out_6947403316902256551);
}
void car_H_29(double *state, double *unused, double *out_2043792986833626850) {
  H_29(state, unused, out_2043792986833626850);
}
void car_h_28(double *state, double *unused, double *out_1344311891628047352) {
  h_28(state, unused, out_1344311891628047352);
}
void car_H_28(double *state, double *unused, double *out_7126192003903157424) {
  H_28(state, unused, out_7126192003903157424);
}
void car_h_31(double *state, double *unused, double *out_2585023898607921181) {
  h_31(state, unused, out_2585023898607921181);
}
void car_H_31(double *state, double *unused, double *out_9006675362946876255) {
  H_31(state, unused, out_9006675362946876255);
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
