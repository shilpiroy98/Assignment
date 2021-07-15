//
//  IngredientInventory.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef IngredientInventory_hpp
#define IngredientInventory_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include "Ingredient.hpp"
#include "json.hpp"
#include "Recipe.hpp"
using json = nlohmann::json;

using namespace std;

class IngredientInventory : public Recipe {
    std::mutex mutex;
public:
    IngredientInventory(json recipe) : Recipe(recipe) {
        
    }
    bool CheckIfSufficient(std::string name, int requiredAmount) {
        if(!CheckIfIngredientPresent(name)) return false;
        return m_ingredients[name]->GetQuantity() >= requiredAmount;
    }
    
    bool DeductIngredientAmount(std::string name, int deductAmount) {
        std::lock_guard<std::mutex> lock(mutex);
        if(!CheckIfSufficient(name, deductAmount)) return false;
        if(deductAmount < 0) return false;
        m_ingredients[name]->DeductAmount(deductAmount);
        return true;
    }
    
    void AddIngredientAmount(std::string name, int increaseAmount) {
        std::lock_guard<std::mutex> lock(mutex);
         if(!CheckIfIngredientPresent(name)) return;
        if(increaseAmount < 0) return;
        m_ingredients[name]->AddAmount(increaseAmount);
    }
};
#endif /* IngredientInventory_hpp */
