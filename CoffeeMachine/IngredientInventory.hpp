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

/*
 Contains list of ingredient items
 -Add item, remove item, check if item is present
 -Check if item is sufficient,
 -Deduct quanities of list of items
 from inventory if deductable
 */
class IngredientInventory : public Recipe {
    std::mutex mutex;
    std::map<std::string, Ingredient*> m_inventory;
    bool m_shouldRefill;

public:
    /*
     Response to send to beverage maker
     in case of success & failure scenarios
     */
    enum DeductResponse {
        NOT_AVAILABLE,
        NOT_SUFFICIENT,
        INCORRECT_PARAMS,
        SUCCESS
    };
    
    // initializes ingredient inventory
    IngredientInventory(json recipe, bool shouldRefill = false) : Recipe(recipe) {
        m_shouldRefill = shouldRefill;
        m_inventory = m_ingredients;
    }

    
    /*
     1. Takes list of ingredients
     2. Checks if ingredients can be deducted by requested amount
     3. Return failure response if not deductable
     3. Deducts amount if deductable
     4. Returns success
     -----------------------------------------------
     Since inventory is shared resource amoung beverages in CoffeeMachine
     While preparing, adding a lock guard to ensure
     no two beverages deduct from inventory at same time (no race conditions)
     ------------------------------------------------------
     */
    pair<DeductResponse, string> DeductIngredientsAmount(std::vector<Ingredient*> ingredients) {
        std::lock_guard<std::mutex> lock(mutex);
        pair<DeductResponse, string> isDeductableResponse = CheckIfDeductableIngredients(ingredients);
        if(isDeductableResponse.first != SUCCESS) return isDeductableResponse;
        for(int i = 0; i < ingredients.size(); i++) {
            string name = ingredients[i]->GetName();
            int deductAmount = ingredients[i]->GetQuantity();
            m_inventory[name]->DeductAmount(deductAmount);
        }

        return make_pair(SUCCESS, "");
    }
    
    // increase ingredient amount in inventory (refill)
    void AddIngredientAmount(std::string name, int increaseAmount) {
         if(!CheckIfIngredientPresent(name)) return;
        if(increaseAmount < 0) return;
        m_inventory[name]->AddAmount(increaseAmount);
    }
    
private:
    /*
     Checks if item is available & sufficient in inventory
     returns appropriate response in case of failure
     */
    pair<DeductResponse, string>  CheckIfDeductableIngredients(std::vector<Ingredient*> ingredients) {
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
        return make_pair(response, "");
    }
    
    // checks if item is present in inventory
    bool CheckIfPresent(std::string name) {
        return m_inventory.find(name) != m_inventory.end();
    }
    
    // checks if item quantity is equal or more than requested
    bool CheckIfSufficient(std::string name, int requiredAmount) {
        if(!CheckIfIngredientPresent(name)) return false;
        return m_inventory[name]->GetQuantity() >= requiredAmount;
    }
    
};
#endif /* IngredientInventory_hpp */
