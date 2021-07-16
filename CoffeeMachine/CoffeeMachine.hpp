//
//  CoffeeMachine.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef CoffeeMachine_hpp
#define CoffeeMachine_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "IngredientInventory.hpp"
#include "BeverageInventory.hpp"
#include "BeverageMaker.hpp"
#include "json.hpp"
#include <thread>
using json = nlohmann::json;

/*
 CoffeeMachine - maintains list of ingredients in machine
 and list of beverages it can prepare
 */
class CoffeeMachine {
    int m_outlets;
    IngredientInventory *m_items;
    BeverageInventory *m_beverages;
    
public:
    CoffeeMachine(int outlets, json beverageList, json ingredientList) {
        m_outlets = outlets;
        m_beverages = new BeverageInventory(beverageList);
        m_items =  new IngredientInventory(ingredientList);
    }
    
    // add beverage name & its recipe to beverage inventory
    void AddBeverage(std::string name, json recipe) {
        if(m_beverages == nullptr) return;
        m_beverages->AddBeverage(name, recipe);
    }
    
    // add ingredient name & quantity to ingredient inventory
    void AddIngredientItems(std::string name, int quantity) {
        if(m_items == nullptr) return;
        m_items->AddIngredient(name, quantity);
    }
    
    vector<std::string> PrepareCoffee() {
        vector<std::string> emp;
         if(m_beverages == nullptr) return emp;
        vector<Beverage*> beverages = m_beverages->GetBeverages();
        vector<std::thread> threads;
        vector<std::string> res(beverages.size());
        for(int i = 0; i < beverages.size(); i++) {
            threads.push_back(std::thread([beverages, i, this, &res]() {
                BeverageMaker::PrepareBeverage(beverages[i], this->m_items, res[i]);
            }));
        }
       
        for(auto& thread : threads){
            thread.join();
        }
       
        return res;
    }
    
};
#endif /* CoffeeMachine_hpp */
