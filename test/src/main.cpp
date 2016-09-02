#include "system/printer.hpp"
#include "math.hpp"

#include <iostream>
#include <sstream>

int main(int argc, const char **argv) {
	using namespace System;
	using namespace Math;

	quat<int> r0 = {0,0,0,0},
		r1 = {1,0,0,0}, ri = {0,1,0,0},
		rj = {0,0,1,0}, rk = {0,0,0,1};
	dual<int> d10 = {r1, r0}, di0 = {ri, r0},
		dj0 = {rj, r0}, dk0 = {rk, r0},
		d01 = {r0, r1}, d0i = {r0, ri},
		d0j = {r0, rj}, d0k = {r0, rk},
		duals[]{d10, di0, dj0, dk0, d01, d0i, d0j, d0k};

	Printer<10> printer;
	std::string rows[10], cols[8];
	dual<int> cells[64];
	rows[0] = rows[9] = "";

	int row = 0;
	for(auto lhs : duals) {
		std::ostringstream oss;
		oss << lhs;
		rows[row+1] = cols[row] = oss.str();
		int col = 0;
		for(auto rhs : duals) {
			cells[row*8+col] = lhs * rhs;
			col++;
		}
		row++;
	}
	printer.push(&rows[0], &rows[0]+10)
		.push<dual<int>, 8, 8>(cells, &cols[0], &cols[8]).level();
	std::cout << printer << std::endl;
}