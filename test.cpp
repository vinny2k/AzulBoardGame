#include <iostream>

#include <vector>
#include <iostream>
int main (void) {

    std::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    vec.erase(vec.begin());

    for (int i = 0; i < 4; ++i) {
        std::cout << vec.at(i) << std::endl;
    }

    return EXIT_SUCCESS;
}