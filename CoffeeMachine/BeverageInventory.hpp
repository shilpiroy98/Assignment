//
//  BeverageInventory.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef BeverageInventory_hpp
#define BeverageInventory_hpp

#include <stdio.h>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include "Beverage.hpp"
#include "json.hpp"
using json = nlohmann::json;

/*
 Maintains list of
 beverages which coffee machine
 can prepare
 - get list of beverages
 - add new beverage in inventory
 - remove existing beverage from inventory
 - add new recipe for beverage
 */
class BeverageInventory {
    std::map<std::string, Beverage*> m_beverages;
    
public:
    
    // initializes beverage inventory
    BeverageInventory(json beverageList) {
        for(auto it = beverageList.begin(); it != beverageList.end(); it++) {
            AddBeverage(it.key(), it.value());
        }
    }
    
    // return list of beverages in inventory
    std::vector<Beverage*> GetBeverages() {
        vector<Beverage*> beverages;
        for(auto it = m_beverages.begin(); it != m_beverages.end(); it++) {
            beverages.push_back(it->second);
        }
        return beverages;
    }
    
    // checks if inventory has the beverage present
    bool CheckIfBeverageExists(std::string name) {
        return m_beverages.find(name) != m_beverages.end();
    }
    
    // add beverage with name and recipe in inventory
    void AddBeverage(std::string name, json recipe) {
        m_beverages[name] = new Beverage(name, recipe);
    }
    
    // add beverage recipe if it exists in inventory
    void AddBeverageRecipe(std::string name, json recipe) {
        if(!CheckIfBeverageExists(name)) return;
        m_beverages[name]->AddRecipe(recipe);
    }
    
    // remove beverage from inventory if it exists
    void RemoveBeverage(std::string name) {
        if(!CheckIfBeverageExists(name)) return;
        m_beverages.erase(name);
    }
};
#endif /* BeverageInventory_hpp */
