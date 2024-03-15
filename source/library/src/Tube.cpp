#include "Tube.hpp"
#include <iostream>
#include <cmath>

using namespace std;

namespace cie {

    namespace pipenetwork {

        Tube::Tube(Node* node1, Node* node2, double diameter) : n1(node1), n2(node2), diameter_(diameter)
        {
            //cout<<"Tube Created"<<endl;                               // constructs a Tube with start node, end node and dia
        }

        double Tube::length() const {
            double len = 0;
            len = sqrt(((n2->x() - n1->x()) * (n2->x() - n1->x())) + ((n2->y() - n1->y()) * (n2->y() - n1->y())));
            return len;
        }

        double Tube::permeability() const {
            double B = 0;
            double l = this->length();                                  // considering the length of that Tube instance
            B = (3.14159265359 * 9.81 * diameter_ * diameter_ * diameter_ * diameter_) / (128 * 0.000001 * l);
            return B;
        }

        const Node* Tube::node1() const {
            return n1;
        }

        const Node* Tube::node2() const {
            return n2;
        }

    }//namespace pipenetwork
}//namespace cie