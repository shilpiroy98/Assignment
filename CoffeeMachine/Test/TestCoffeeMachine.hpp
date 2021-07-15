//
//  TestCoffeeMachine.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef TestCoffeeMachine_hpp
#define TestCoffeeMachine_hpp

#include <stdio.h>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include "CoffeeMachine.hpp"


using json = nlohmann::json;

class TestCoffeeMachine {
public:
    void RunTestCase1() {
        std::cout<<"Running test case 1....\n\n-----------\n";
         auto j = json::parse(R"(
                               {
                                 "machine": {
                                   "outlets": {
                                     "count_n": 4
                                   },
                                   "total_items_quantity": {
                                     "hot_water": 500,
                                     "hot_milk": 500,
                                     "ginger_syrup": 100,
                                     "sugar_syrup": 100,
                                     "tea_leaves_syrup": 100
                                   },
                                   "beverages": {
                                     "hot_tea": {
                                       "hot_water": 200,
                                       "hot_milk": 100,
                                       "ginger_syrup": 10,
                                       "sugar_syrup": 10,
                                       "tea_leaves_syrup": 30
                                     },
                                     "hot_coffee": {
                                       "hot_water": 100,
                                       "ginger_syrup": 30,
                                       "hot_milk": 400,
                                       "sugar_syrup": 50,
                                       "tea_leaves_syrup": 30
                                     },
                                     "black_tea": {
                                       "hot_water": 300,
                                       "ginger_syrup": 30,
                                       "sugar_syrup": 50,
                                       "tea_leaves_syrup": 30
                                     },
                                     "green_tea": {
                                       "hot_water": 100,
                                       "ginger_syrup": 30,
                                       "sugar_syrup": 50,
                                       "green_mixture": 30
                                     }
                                   }
                                 }
                               }

                               )");
        
        std::cout << std::setw(4) << j << std::endl;
        std::cout<<"\n----------\n";

         CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);

         
         vector<vector<std::string> > expectedResults;
         vector<std::string> expectedResult1;
         expectedResult1.push_back("hot_tea is prepared");
         expectedResult1.push_back("hot_coffee is prepared");
         expectedResult1.push_back("green_tea can't be prepared because green_mixture is not available");
         expectedResult1.push_back("black_tea can't be prepared because hot_water is not available");
         
        vector<std::string> expectedResult2;
        expectedResult2.push_back("hot_tea is prepared");
        expectedResult2.push_back("black_tea is prepared");
        expectedResult2.push_back("green_tea can't be prepared because green_mixture is not available");
        expectedResult2.push_back("hot_coffee can't be prepared because hot_water is not available");


         
         vector<std::string> expectedResult3;
         expectedResult3.push_back("hot_coffee is prepared");
         expectedResult3.push_back("black_tea is prepared");
         expectedResult3.push_back("green_tea can't be prepared because green_mixture is not available");
         expectedResult3.push_back("hot_tea can't be prepared because hot_water is not available");
         
         expectedResults.push_back(expectedResult1);
         expectedResults.push_back(expectedResult2);
         expectedResults.push_back(expectedResult3);
         for(int i = 0; i < expectedResults.size(); i++) {
             sort(expectedResults[i].begin(), expectedResults[i].end());
         }
         
         vector<std::string> actualResult = cm->PrepareCoffee();
         sort(actualResult.begin(), actualResult.end());
         bool isExpected = false, idx = -1;
          for(int i = 0; i < expectedResults.size(); i++) {
              bool result = std::equal(actualResult.begin(), actualResult.end(), expectedResults[i].begin());
              if(result) {
                  isExpected = true;
                  idx = i;
                  break;
              }
          }
         assert(isExpected == true);
         std::cout<<"Matches output id: "<<idx + 1<<"\n"<<"-------------\n";
    }
    
    void RunTestCase2() {

         auto j = json::parse(R"(
                               {
                                 "machine": {
                                   "outlets": {
                                     "count_n": 3
                                   },
                                   "total_items_quantity": {
                                     "hot_water": 20,
                                     "hot_milk": 20,
                                     "ginger_syrup": 20,
                                     "sugar_syrup": 20,
                                     "tea_leaves_syrup": 20
                                   },
                                   "beverages": {
                                     "dark_coffee": {
                                       "coffee_beans": 25
                                     },
                                     "capuchhino_coffee": {
                                       "hot_water": 10
                                     },
                                     "latte_coffee": {
                                       "hot_water": 100,
                                       "ginger_syrup": 100,
                                       "tea_leaves_syrup": 30
                                     }
                                   }
                                 }
                               }

                               )");

         CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);

//
//         vector<vector<std::string> > expectedResults;
//         vector<std::string> expectedResult1;
//         expectedResult1.push_back("hot_tea is prepared");
//         expectedResult1.push_back("hot_coffee is prepared");
//         expectedResult1.push_back("green_tea can't be prepared because green_mixture is not available");
//         expectedResult1.push_back("black_tea can't be prepared because hot_water is not available");
//
//        vector<std::string> expectedResult2;
//        expectedResult2.push_back("hot_tea is prepared");
//        expectedResult2.push_back("black_tea is prepared");
//        expectedResult2.push_back("green_tea can't be prepared because green_mixture is not available");
//        expectedResult2.push_back("hot_coffee can't be prepared because hot_water is not available");
//
//
//
//         vector<std::string> expectedResult3;
//         expectedResult3.push_back("hot_coffee is prepared");
//         expectedResult3.push_back("black_tea is prepared");
//         expectedResult3.push_back("green_tea can't be prepared because green_mixture is not available");
//         expectedResult3.push_back("hot_tea can't be prepared because hot_water is not available");
//
//         expectedResults.push_back(expectedResult1);
//         expectedResults.push_back(expectedResult2);
//         expectedResults.push_back(expectedResult3);
//         for(int i = 0; i < expectedResults.size(); i++) {
//             sort(expectedResults[i].begin(), expectedResults[i].end());
//         }
         
//         vector<std::string> actualResult = cm->PrepareCoffee();
//         sort(actualResult.begin(), actualResult.end());
//         bool isExpected = false, idx = -1;
//          for(int i = 0; i < expectedResults.size(); i++) {
//              bool result = std::equal(actualResult.begin(), actualResult.end(), expectedResults[i].begin());
//              if(result) {
//                  isExpected = true;
//                  idx = i;
//                  break;
//              }
//          }
//         assert(isExpected == true);
//         std::cout<<"Matches output id: "<<idx + 1<<"\n";
    }
    
    void RunTestCase3() {

        auto j = json::parse(R"(
                            {
                                "machine": {
                                  "outlets": {
                                    "count_n": 0
                                  },
                                  "total_items_quantity": {

                                  },
                                  "beverages": {

                                  }
                                }
                              }

                              )");

        CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);
    }
    
    
    void RunTestCase4() {

        auto j = json::parse(R"(
                            {
                                "machine": {
                                  "outlets": {
                                    "count_n": 0
                                  },
                                  "total_items_quantity": {

                                  },
                                  "beverages": {

                                  }
                                }
                              }

                              )");

        CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);
    }
public:
    void RunTests() {
        RunTestCase1();
    }
};
#endif /* TestCoffeeMachine_hpp */
