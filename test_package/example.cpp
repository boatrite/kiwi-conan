#include "kiwi.h"

#include <iostream>

// https://kiwisolver.readthedocs.io/en/latest/basis/basic_systems.html
int main() {
    // The first things that need to be defined are variables. Variables
    // represent the values which the solver will be trying to determine.
    // Variables are represented by Variable objects which can be created as
    // follow:
    kiwi::Variable x1("x1");
    kiwi::Variable x2("x2");
    kiwi::Variable xm("xm");

    // Now that we have some variables we can define our constraints.
    kiwi::Constraint constraints[] = {
        kiwi::Constraint {x1 >= 0},
        kiwi::Constraint {x2 <= 100},
        kiwi::Constraint {x2 >= x1 + 20},
        kiwi::Constraint {xm == (x1 + x2) / 2},
    };

    // The next step is to add them to our solver, which is an instance of
    // Solver:
    kiwi::Solver solver;

    for (auto& constraint : constraints) {
        solver.addConstraint(constraint);
    }
    solver.updateVariables();
    std::cout << "xm == " << xm.value() << ", x1 == " << x1.value() << ", x2 == " << x2.value() << std::endl;

    // So far we have defined a system representing three points on the segment
    // [0, 100], with one of them being the middle of the others which cannot
    // get closer than 10. All those constraints have to be satisfied, in the
    // context of cassowary they are “required” constraints.

    // Add weak constraint
    solver.addConstraint(x1 == 40 | kiwi::strength::weak);

    // Add edit variable
    solver.addEditVariable(xm, kiwi::strength::strong);
    solver.suggestValue(xm, 60);

    // Needs to be called before calling value() on Variables.
    solver.updateVariables();
    std::cout << "xm == " << xm.value() << ", x1 == " << x1.value() << ", x2 == " << x2.value() << std::endl;
}
