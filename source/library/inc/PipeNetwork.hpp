#pragma once
#include <string>
#include <vector>
#include "Node.hpp"
#include "Tube.hpp"

namespace cie {

    namespace pipenetwork {

        // class declaration
        class PipeNetwork
        {
        private:

            std::vector<Node> nodes;        // containing all nodes
            std::vector<Tube> tubes;        // containing all tubes
            const std::string& filename_;

        public:

            PipeNetwork(std::string filename);             // user defined constructor
            std::vector<double> computeFluxes() const;     // computes fluxes and returns a vector
        };
    }//namespace pipenetwork
}//namespace cie