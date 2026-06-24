#ifndef CARGOMANAGEMENTSYSTEM_CARGOBAY_H
#define CARGOMANAGEMENTSYSTEM_CARGOBAY_H

#include <memory>
#include <vector>
#include "Cargo.h"


class CargoBay {
private:
    double width = 0.0;
    double length = 0.0;
    double height = 0.0;

    double maxVolume = 0.0;
    double occupiedVolume = 0.0;

    std::vector<std::unique_ptr<Cargo>> cargoHold;

public:
    CargoBay(double w, double l, double h);

    bool addCargo(std::unique_ptr<Cargo> item);
    void packItemsHeuristic();
    void printDiagnosticReport() const;

    [[nodiscard]] double getWidth() const { return width; }
    [[nodiscard]] double getLength() const { return length; }
    [[nodiscard]] double getHeight() const { return height; }
    [[nodiscard]] double getAvailableVolume() const { return maxVolume - occupiedVolume; }

    [[nodiscard]] const std::vector<std::unique_ptr<Cargo>>& getItems() const { return cargoHold; }
};


#endif
