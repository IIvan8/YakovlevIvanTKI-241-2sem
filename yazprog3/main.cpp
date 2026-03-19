#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<std::string> V1 = {
        "WHITE",      
        "BLUE",      
        "GREEN",     
        "PINK",      
        "GOLD",      
        "GRAY"       
    };

    std::vector<std::string> V2 = {
        "BROWN",     
        "BLACK",     
        "RED",     
        "PURPLE",    
        "ORANGE",    
        "BEIGE"      
    };

    std::map<int, std::vector<std::string>> M;

    for (auto it = V2.begin(); it != V2.end(); ++it) {
        const std::string& word = *it;
        int length = word.size();
        M[length].push_back(word);  
    }

    std::vector<std::string> sortedV1 = V1;
    std::sort(sortedV1.begin(), sortedV1.end());

    std::vector<std::pair<std::string, std::string>> V;

    for (auto it1 = sortedV1.begin(); it1 != sortedV1.end(); ++it1) {
        const std::string& word1 = *it1;
        int len = word1.size();

        auto mapIt = M.find(len);
        if (mapIt != M.end()) {
            std::vector<std::string> v2words = mapIt->second;

            std::sort(v2words.begin(), v2words.end(),
                std::greater<std::string>());

            for (auto it2 = v2words.begin(); it2 != v2words.end(); ++it2) {
                V.push_back({ word1, *it2 });
            }
        }
    }

    std::cout << "Размер вектора V: " << V.size() << std::endl;
    std::cout << "Элементы вектора V (пары цветов одинаковой длины):" << std::endl;

    for (auto it = V.begin(); it != V.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }

    return 0;
}