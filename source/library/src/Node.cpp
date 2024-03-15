#include "Node.hpp"
#include <iostream>

using namespace std;

namespace cie {

    namespace pipenetwork {

        Node::Node(double x, double y, double flow, int id) : x_(x), y_(y), flow_(flow), id_(id)
        {
            //cout<<"Node Created"<<endl;                                  // constructs a Node with values x,y,flow,id
        }

        double Node::x() const {
            return x_;
        }

        double Node::y() const {
            return y_;
        }

        double Node::flow() const {
            return flow_;
        }

        int Node::id() const {
            return id_;
        }
    }//namespace pipenetwork
}//namespace cie