#include "model/obj.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <type_traits>

int main(int argc, const char **argv) {
	using namespace Model;
	obj_t obj;
	auto fname = "share/test.obj";
	endl(std::cout << "File: " << fname);
	switch(obj_t::load(fname, obj)) {
		case obj_t::e_err_io:
			std::cout << "Status: I/O Error\n" << std::endl;
			break;
		case obj_t::e_ok:
			std::cout << "Status: OK\n" << std::endl;
			break;
		case obj_t::e_err_unknown:
			std::cout << "Status: Unknown\n" << std::endl;
			break;
		default:
			break;
	}

	int counter = 0, fCounter = 0, iCounter = 0, sCounter = 0;
	for(auto beg = std::begin(obj.types); beg != std::end(obj.types); beg++) {
		int nf = obj.nFloats[counter], ni = obj.nInts[counter],
				ns = obj.nStrings[counter];
		for(int i = 0; i < nf; ++i) {
			//std::cout << "i = " << i << ", fc = " << fCounter << std::endl;
			std::cout << obj.floats[i+fCounter++] << " ";
		}
		for(int i = 0; i < ni; ++i) {
			//std::cout << "i = " << i << ", ic = " << iCounter << std::endl;
			std::cout << obj.ints[i+iCounter++] << " ";
		}
		for(int i = 0; i < ns; ++i) {
			//std::cout << "i = " << i << ", sc = " << sCounter << std::endl;
			std::cout << obj.strings[i+sCounter++] << " ";
		}
		counter++;
		endl(std::cout);
	}
}
