#pragma once
#include <string>

namespace cie {
    namespace pipenetwork {

        class Node
        {
        private:
            const double x_;
            const double y_;
            const double flow_;
            const int id_;

        public:
            Node(double x, double y, double flow, int id);              // user defined constructor for Node
            double x() const;
            double y() const;                                          // returns  
            double flow() const;                                       // private
            int id() const;                                            // variables
        };
    }// namespace pipenetwork
}// namespace cie