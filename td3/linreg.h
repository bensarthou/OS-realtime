#include <cstdlib>
#include <vector>
//! @credit: Grégoire Roussel

/*!
\brief compute slope parameters with linear regression
\param x: reference to double vector of x values for the slope
\param y: reference to double vector of y values for the slope
\param m: reference to double, value to store the slope ratio after computation
\param p: reference to double, value to store the intercept
\param r: reference to double, value to store the correlation r2 factor
*/
void linear_regression(std::vector<double> const &x, std::vector<double> const &y, double &m, double &p, double &r);
