#ifndef CARGOMANAGEMENTSYSTEM_CARGOSPHERE_H
#define CARGOMANAGEMENTSYSTEM_CARGOSPHERE_H
#include "Cargo.h"


class CargoSphere : public Cargo {
private:
    double radius;
public:
    explicit CargoSphere(double radius);

    [[nodiscard]] std::string getType() const override;
    [[nodiscard]] double getRadius() const;
};


#endif
