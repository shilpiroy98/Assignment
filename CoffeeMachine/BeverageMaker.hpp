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
        bool isPrepared = true;
        for(int i = 0; i < recipe.size(); i++) {
            bool isDeducted = items->DeductIngredientAmount(recipe[i]->GetName(), recipe[i]->GetQuantity());
            if(!isDeducted) {
               isPrepared = false;
               res = beverage->GetName() + " can't be prepared because " + recipe[i]->GetName() + " is not available";
                printf("%s can't be prepared because %s is not available\n", beverage->GetName().c_str(), recipe[i]->GetName().c_str());
                break;
            }
        }

        if(isPrepared) {
            printf("%s is prepared\n", beverage->GetName().c_str());
            res = beverage->GetName() + " is prepared";
        }
    }
};
#endif /* BeverageMaker_hpp */
