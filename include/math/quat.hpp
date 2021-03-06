#ifndef MATH_QUAT_HPP
#define MATH_QUAT_HPP

#include <boost/operators.hpp>

namespace Math {

	template<typename R = float>
	struct quat: public boost::operators<quat<R>> {
		R w, x, y, z;
		
		/* Unary operators */

		/** Multiplicative inverse */
		quat<R> operator!(void) const;
		/** Additive inverse */
		quat<R> operator-(void) const;
		/** Conjugate */
		quat<R> operator~(void) const;
		/** Cast operator, as Euclidean norm */
		explicit operator R(void) const;
		/** Squared Euclidean norm */
		R operator()(void) const;
		/** Simple promotion */
		explicit operator dual<R>(void) const;

		/** Distributes equality test */
		bool operator==(quat<R> const& rhs) const;
		/** Apply (lhs * rhs * ~lhs) */
		quat<R> operator()(quat<R> const& rhs) const;
		/** Apply (lhs * rhs * ~lhs) */
		dual<R> operator()(dual<R> const& rhs) const;
		
		/*quat<R> operator+(quat<R> const& rhs) const;
		quat<R> operator-(quat<R> const& rhs) const;
		quat<R> operator/(quat<R> const& rhs) const;
		quat<R> operator/(R const& rhs) const;*/


		quat<R>& operator+=(quat<R> const& rhs);
		quat<R>& operator-=(quat<R> const& rhs);
		quat<R>& operator*=(R const& rhs);
		quat<R>& operator*=(quat<R> const& rhs);
		quat<R>& operator/=(R const& rhs);
		quat<R>& operator/=(quat<R> const& rhs);

		quat(void) = default;
		quat(const R w, const R x = 0, const R y = 0, const R z = 0):
			w(w), x(x), y(y), z(z) {}
	};
	template<typename R>
	quat<R> quat<R>::operator-(void) const {
		return {-w,-x,-y,-z};
	}
	template<typename R>
	quat<R> quat<R>::operator!(void) const {
		return ~(*this)/((*this)());
	}
	template<typename R>
	quat<R> quat<R>::operator~(void) const {
		return {w,-x,-y,-z};
	}
	template<typename R>
	quat<R>::operator R(void) const {
		return sqrt((*this)());
	}
	template<typename R>
	R quat<R>::operator()(void) const {
		return w*w + x*x + y*y + z*z;
	}
	template<typename R>
	quat<R>::operator dual<R>(void) const {
		return {*this, 0};
	}

	template<typename R>
	bool quat<R>::operator==(quat<R> const& rhs) const {
		return w == rhs.w && x == rhs.x 
			&& y == rhs.y && z == rhs.z;
	}
	template<typename R>
	quat<R> quat<R>::operator()(quat<R> const& rhs) const {
		return *this * rhs * ~*this;
	}

	template<typename R>
	quat<R>& quat<R>::operator+=(quat<R> const& rhs) {
		w += rhs.w; x += rhs.x; y += rhs.y; z += rhs.z;
		return *this;
	}
	template<typename R>
	quat<R>& quat<R>::operator-=(quat<R> const& rhs) {
		w -= rhs.w; x -= rhs.x; y -= rhs.y; z -= rhs.z;
		return *this;
	}
	template<typename R>
	quat<R>& quat<R>::operator*=(R const& rhs) {
		w *= rhs; x *= rhs;
		y *= rhs; z *= rhs;
		return *this;
	}
	template<typename R>
	quat<R>& quat<R>::operator*=(quat<R> const& r) {
		R lw = w, lx = x, ly = y, lz = z,
		  rw = r.w, rx = r.x, ry = r.y, rz = r.z;
		w = lw*rw - lx*rx - ly*ry - lz*rz;
		x = lw*rx + lx*rw + ly*rz - lz*ry;
		y = lw*ry - lx*rz + ly*rw + lz*rx;
		z = lw*rz + lx*ry - ly*rx + lz*rw;
		return *this;
	}
}

#endif
