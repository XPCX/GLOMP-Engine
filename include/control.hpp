#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "model.hpp"
#include "view.hpp"

namespace Control {
	typedef enum : unsigned char {
		e_tid_view=0, ///< The view task ID, necessarily 0 (master)
		e_tid_model,  ///< The model task ID
		e_tid_total   ///< The total number of enumerated tasks
	} e_tid; ///< The ID of a task

	/// A data structure controlling both model and view
	struct control : public Util::task {
		std::vector<std::string> errors;
		const Model::model &model;
		View::view &viewer;

		float r_dead = .125f;
		/** Joystick deadzone; zeroes inputs below threshold and normalizes
		 * inputs above threshold.
		 * @param x First axis
		 * @param y Second axis
		 */
		void deadzone(float &x, float &y);
		
		bool init(std::atomic_bool &alive) override;
		bool poll(std::atomic_bool &alive) override;
		bool run(std::atomic_bool &alive) override;

		/** Constructor; initializes and applies shaders
 		 * @param alive Shared state; false signals shutdown
 		 */
		control(std::atomic_bool &alive,
				const Model::model &model,
				View::view &viewer);
	};
}


#endif
