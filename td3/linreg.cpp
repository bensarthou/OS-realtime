#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <cmath>

#include "linreg.h"

void linear_regression(std::vector<double> const &x, std::vector<double> const &y, double &m, double &p, double &r)
{
	// Equation: m*x+p
	if (x.size() != y.size())
	{
		printf("%ld:%ld", x.size(), y.size());
		throw std::runtime_error{"Vectors don't have the same size"};
	}
	const double n = x.size();
	const double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
	const double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
	const double sum_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
	const double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
	const double sum_yy = std::inner_product(y.begin(), y.end(), y.begin(), 0.0);
	m = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
	p = (sum_y - m * sum_x) / n;

	// double SSres = 0;
	// double SStot = 0;
	// for(size_t i = 0; i < n; i++)
	// {
	//     SSres += pow(y[i] - m*x[i] - p, 2);
	//     SStot += pow(y[i] - sum_x/n, 2);
	// }

	// False equation
	// r = (n * sum_xy - sum_x * sum_y) / sqrt( (n * sum_xx - sum_x*sum_x) * (n* sum_yy - sum_y*sum_y));
}
