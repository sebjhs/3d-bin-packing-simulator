#include "CargoBay.h"
#include <iostream>
#include <iomanip>

CargoBay::CargoBay(double w, double l, double h) : width(w), length(l), height(h) {
    maxVolume = w * l * h;
}

bool CargoBay::addCargo(std::unique_ptr<Cargo> item) {
    if (occupiedVolume + item->getVolume() > maxVolume) {
        std::cout << "[SYSTEM ERROR] Not enough volume remaining in the cargo bay!\n";
        return false;
    }

    occupiedVolume += item->getVolume();

    cargoHold.push_back(std::move(item));
    return true;
}

void CargoBay::packItemsHeuristic() {
    // TODO: Calculation logic
}

void CargoBay::printDiagnosticReport() const {
    std::cout << "\n====================================================================\n";
    std::cout << "                    INTERSTELLAR DIAGNOSTIC REPORT                  \n";
    std::cout << "====================================================================\n";

    std::cout << std::fixed << std::setprecision(2); // lock all decimals to 2 places
    std::cout << "> Bay Dimensions     : " << width << "m x " << length << "m x " << height << "m\n";
    std::cout << "> Total Max Capacity : " << maxVolume << " m³\n";
    std::cout << "> Total Occupied Space: " << occupiedVolume << " m³\n";
    std::cout << "> Total Available Room: " << getAvailableVolume() << " m³\n";

    std::cout << "\n====================================================================\n";
    std::cout << "                     CURRENT CARGO HOLD MANIFEST                    \n";
    std::cout << "====================================================================\n";

    if (cargoHold.empty()) {
        std::cout << " [SYSTEM NOTE] Cargo bay is currently completely empty.\n";
    } else {
        std::cout << std::left
                  << std::setw(4)  << "#"
                  << std::setw(12) << "Type"
                  << std::setw(16) << "Area (m²)"
                  << std::setw(16) << "Volume (m³)" << "\n";
        std::cout << "--------------------------------------------------------------------\n";

        for (size_t i = 0; i < cargoHold.size(); i++) {
            std::cout << std::left
                      << std::setw(4)  << (i + 1)
                      << std::setw(12) << cargoHold[i]->getType()
                      << std::setw(16) << cargoHold[i]->getArea()
                      << std::setw(16) << cargoHold[i]->getVolume() << "\n";
        }
    }
    std::cout << "====================================================================\n\n";
}
