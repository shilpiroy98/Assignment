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
    std::map<std::string, Ingredient*> m_inventory;
    bool m_shouldRefill;
    static const int REFILL_AMOUNT = 50;

public:
    enum DeductResponse {
        NOT_AVAILABLE,
        NOT_SUFFICIENT,
        INCORRECT_PARAMS,
        SUCCESS
    };
    
    IngredientInventory(json recipe, bool shouldRefill = false) : Recipe(recipe) {
        m_shouldRefill = shouldRefill;
        m_inventory = m_ingredients;
    }
    
    bool CheckIfPresent(std::string name) {
        return m_inventory.find(name) != m_inventory.end();
    }
    
    bool CheckIfSufficient(std::string name, int requiredAmount) {

        if(!CheckIfIngredientPresent(name)) return false;
        return m_inventory[name]->GetQuantity() >= requiredAmount;
    }
    
    
    pair<DeductResponse, string> DeductIngredientsAmount(std::vector<Ingredient*> ingredients) {
        std::lock_guard<std::mutex> lock(mutex);
        DeductResponse response = SUCCESS;
        for(int i = 0; i < ingredients.size(); i++) {
            string name = ingredients[i]->GetName();
            int deductAmount = ingredients[i]->GetQuantity();
            if(!CheckIfPresent(name)) {
                response = NOT_AVAILABLE;
            }
            else if(!CheckIfSufficient(name, deductAmount)) {
                response = NOT_SUFFICIENT;
            }
            else if(deductAmount < 0) {
                response = INCORRECT_PARAMS;
            }
            if(response != SUCCESS) return make_pair(response, name);
        }
        
        for(int i = 0; i < ingredients.size(); i++) {
            string name = ingredients[i]->GetName();
            int deductAmount = ingredients[i]->GetQuantity();
            m_inventory[name]->DeductAmount(deductAmount);
        }

        return make_pair(response, "");
    }
    
    void AddIngredientAmount(std::string name, int increaseAmount) {
         if(!CheckIfIngredientPresent(name)) return;
        if(increaseAmount < 0) return;
        m_inventory[name]->AddAmount(increaseAmount);
    }
};
#endif /* IngredientInventory_hpp */
