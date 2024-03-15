#pragma once

#include "Node.hpp"
#include <string>

namespace cie {

	namespace pipenetwork {

		class Tube {
		private:
			Node* n1;
			Node* n2;
			double diameter_;

		public:
			Tube(Node* node1, Node* node2, double diameter);				// user defined constructor for Tube
			double length() const;
			double permeability() const;
			const Node* node1() const;										// returns n1
			const Node* node2() const;										// and n2
		};

	}//namespace pipenetwork
}//namespace cie