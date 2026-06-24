#include <iostream>
#include <cmath>
#include <memory>
#include "CargoBay.h"
#include "CargoCube.h"
#include "CargoSphere.h"

CargoBay setupCargoBay();
void runSystemLoop(CargoBay& shipBay);

int main() {
    std::cout << "=============================================\n";
    std::cout << "     INTERSTELLAR CARGO SYSTEM ACTIVATED\n";
    std::cout << "=============================================\n";

    CargoBay myShipBay = setupCargoBay();

    if (myShipBay.getWidth() <= 0.0) {
        std::cout << "Run aborted: Invalid cargo bay initialisation.\n";
        return 1;
    }

    runSystemLoop(myShipBay);

    return 0;
}

/**
 * @brief Prompts the user for physical dimensions and initializes the CargoBay object.
 */
CargoBay setupCargoBay() {
    double width, length, height;
    std::cout << "Enter Cargo Dimensions (width, length, height in meters): ";

    if (!(std::cin >> width >> length >> height) || width <= 0 || length <= 0 || height <= 0) {
        return {0, 0, 0};
    }

    double calculatedVolume = width * length * height;
    if (calculatedVolume > 5000.0) {
        std::cout << "\n!!! SAFETY WARNING !!!: Cargo volume (" << calculatedVolume << " m³) exceeds maximum limit.\n";
        std::cout << "Scaling dimensions safely down to structural safety ceiling limits.\n";
        const double scaleFactor = std::cbrt(5000.0 / calculatedVolume);
        width *= scaleFactor;
        length *= scaleFactor;
        height *= scaleFactor;
    }

    return {width, length, height};
}

/**
 * @brief Handles user console inputs and routes commands directly to the CargoBay manager.
 */
void runSystemLoop(CargoBay& shipBay) {
    bool running = true;

    while (running) {
        std::cout << "1. Load a Heavy Cargo Cube\n";
        std::cout << "2. Load a Spherical Fuel Core\n";
        std::cout << "3. Check Cargo Hold Status (Diagnostic Report)\n";
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

                if (shipBay.addCargo(std::make_unique<CargoCube>(sideLength))) {
                    std::cout << "Cargo Cube successfully loaded into storage matrix.\n\n";
                }
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

                if (shipBay.addCargo(std::make_unique<CargoSphere>(radius))) {
                    std::cout << "Spherical Fuel Core successfully loaded into storage matrix.\n\n";
                }
                break;
            }
            case 3: {
                shipBay.printDiagnosticReport();
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