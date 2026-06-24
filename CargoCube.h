#ifndef HELLOWORLD_CARGOCUBE_H
#define HELLOWORLD_CARGOCUBE_H

#include "Cargo.h"

class CargoCube : public Cargo {
private:
    double sideLength;
public:
    explicit CargoCube(double sideLength);

    [[nodiscard]] std::string getType() const override;
    [[nodiscard]] double getSideLength() const;
};

#endif
