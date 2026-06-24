#include <iostream>
#include <vector>
#include <cmath>
#include "CargoCube.h"
#include "CargoSphere.h"
#include <iomanip>

void run(const double maxVolume) {
    bool running = true;
    double occupiedVolume = 0.0;
    std::vector<std::unique_ptr<Cargo>> cargoHold;

    while (running) {
        std::cout << "1. Load a Heavy Cargo Cube\n";
        std::cout << "2. Load a Spherical Fuel Core\n";
        std::cout << "3. Check Cargo Hold Status\n";
        std::cout << "4. Exit System\n\n";
        std::cout << "Select an option: ";

        int option;
        if (!(std::cin >> option)) {
            std::cout << "Invalid terminal input. Exiting.\n" << std::endl;
             break;
        }

        switch (option) {
            case 1: {
                std::cout << "Enter side length of cube: ";
                double sideLength;
                std::cin >> sideLength;

                if (sideLength <= 0) {
                    std::cout << "Invalid dimensions! Aborting load operation.\n\n";
                   break;
                }

                cargoHold.push_back(std::make_unique<CargoCube>(sideLength));

                std::cout << "Cargo Cube Loaded!\n";
                std::cout << "Area: " << cargoHold.back()->getArea() << "m², Volume: " << cargoHold.back()->getVolume() << "m³\n\n";
                occupiedVolume += cargoHold.back()->getVolume();
                break;
            }
            case 2: {
                std::cout << "Enter radius of sphere: ";
                double radius;
                std::cin >> radius;

                if (radius <= 0) {
                    std::cout << "Invalid dimensions! Aborting load operation.\n\n";
                    break;
                }

                cargoHold.push_back(std::make_unique<CargoSphere>(radius));

                std::cout << "Spherical Cube Core Loaded!\n";
                std::cout << "Area: " << cargoHold.back()->getArea() << "m², Volume: " << cargoHold.back()->getVolume() << "m³\n\n";
                occupiedVolume += cargoHold.back()->getVolume();
                break;
            }
            case 3: {
                std::cout << "\n====================================================================\n";
                std::cout << "                    INTERSTELLAR DIAGNOSTIC REPORT                  \n";
                std::cout << "====================================================================\n";

                std::cout << std::fixed << std::setprecision(2); // lock all decimals to 2 places
                std::cout << "> Total Max Capacity : " << maxVolume << " m³\n";
                std::cout << "> Total Occupied Space: " << occupiedVolume << " m³\n";
                std::cout << "> Total Available Room: " << (maxVolume - occupiedVolume) << " m³\n";

                std::cout << "\n====================================================================\n";
                std::cout << "                     CURRENT CARGO HOLD MANIFEST                    \n";
                std::cout << "====================================================================\n";

                if (cargoHold.empty()) {
                    std::cout << " [SYSTEM NOTE] Cargo bay is currently completely empty.\n";
                } else {
                    // print Table Headers with explicit column widths
                    std::cout << std::left
                              << std::setw(4)  << "#"
                              << std::setw(12) << "Type"
                              << std::setw(16) << "Area (m²)"
                              << std::setw(16) << "Volume (m³)" << "\n";
                    std::cout << "--------------------------------------------------------------------\n";

                    // print each polymorphic item matching the column widths
                    for (size_t i = 0; i < cargoHold.size(); i++) {
                        std::cout << std::left
                                  << std::setw(4)  << (i + 1)
                                  << std::setw(12) << cargoHold[i]->getType()
                                  << std::setw(16) << cargoHold[i]->getArea()
                                  << std::setw(16) << cargoHold[i]->getVolume() << "\n";
                    }
                }

                std::cout << "====================================================================\n\n";
                break;
            }
            case 4:
                running = false;
                std::cout << "Powering down systems. Goodbye, Captain.\n";
                break;
            default:
                std::cout << "Invalid selection. Please try again.\n\n";
                break;
        }
    }
}

/**
 * @brief Prompts the user for three dimensions and returns them as a vector.
 * @return vector<double> containing {width, length, height}, or an empty vector on failure.
 */
double setupCargoBay() {
    double width, length, height;
    std::cout<<"Enter Cargo Dimensions (width, length, height): ";
    if (!(std::cin >> width >> length >> height)) {
        return 0.0;
    }

    double volume = width * length * height;

    if (volume > 5000.0) {
        volume = std::floor(5000.0);
        std::cout << "\n!!! SAFETY WARNING !!!: Cargo volume exceeds maximum limit.\n";
        std::cout << "Cargo bay set to structural maximum ceiling of 5000 units.\n";
    }

    return volume;
}



int main() {
    double bayVolume = setupCargoBay();
    if (bayVolume <= 0.0) {
        std::cout << "Run aborted: Invalid cargo bay initialisation.\n";
        return 1;
    }

    std::cout << "=============================================\n";
    std::cout << "     INTERSTELLAR CARGO SYSTEM ACTIVATED\n";
    std::cout << "=============================================\n";

    run(bayVolume);
    return 0;
}