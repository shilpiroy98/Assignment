//
//  BeverageMaker.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef BeverageMaker_hpp
#define BeverageMaker_hpp

#include <stdio.h>
#include <iostream>
#include "Beverage.hpp"
#include <thread>
#include "IngredientInventory.hpp"

class BeverageMaker {

public:
    static void PrepareBeverage(Beverage *beverage, IngredientInventory *items, std::string &res) {

        vector<Ingredient*> recipe = beverage->GetRecipe();
        pair<IngredientInventory::DeductResponse, string> response = items->DeductIngredientsAmount(recipe);
        if(response.first == IngredientInventory::SUCCESS) {
            res = beverage->GetName() + " is prepared";
        }
        else {
            string to_add;
            switch(response.first) {
                    case IngredientInventory::NOT_AVAILABLE:
                        to_add = "not available";
                        break;
                    case IngredientInventory::NOT_SUFFICIENT:
                        to_add = "not sufficient";
                        break;
                    default:
                        to_add = "incorrect params";
                        break;
                }
            res = beverage->GetName() + " can't be prepared because " + response.second + " is " + to_add;
        }
        printf("%s\n", res.c_str());
    }

};
#endif /* BeverageMaker_hpp */
