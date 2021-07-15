//
//  main.cpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 14/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#include <iostream>
#include "TestCoffeeMachine.hpp"

int main(int argc, const char * argv[]) {

    TestCoffeeMachine *testCoffeeMachine = new TestCoffeeMachine();
    testCoffeeMachine->RunTests();
    return 0;

}
