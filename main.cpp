#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <stack> // se agrega esta librería para usar std::stack

int h4(std::string s) {
    int c = 0;
    if (s[0] != 'a' && s[0] != 'b')
        c = 1;
    for (int i = 0; i < s.size() - 1; i++)
        if (std::abs(s[i] - s[i + 1]) > 1)
            c++;
    return c;
}

void flip(std::string& str, int i) {
    std::reverse(str.begin(), str.begin() + i + 1);
}

std::string ida_star(std::string start, std::string end, int depth_limit, int& count, int f_limit) {
    int next_f_limit = INT_MAX;
    std::set<std::string> visited;
    std::vector<std::string> path;
    std::stack<std::string> dfs_stack;
    dfs_stack.push(start);
    path.push_back(start);
    visited.insert(start);
    count++;
    while (!dfs_stack.empty()) {
        std::string curr = dfs_stack.top();
        dfs_stack.pop();
        path.pop_back();

        if (curr == end)
            return curr;

        if (path.size() >= depth_limit)
            continue;

        for (int i = 1; i < curr.size(); i++) {
            std::string next = curr;
            flip(next, i);
            if (visited.count(next) == 0 && h4(next) + path.size() + 1 <= f_limit) {
                visited.insert(next);
                dfs_stack.push(next);
                path.push_back(next);
                count++;
            }
            else if (h4(next) + path.size() + 1 < next_f_limit) {
                next_f_limit = h4(next) + path.size() + 1;
            }
        }
    }

    return "";
}

int main() {
    std::string pancake = "abcdefghijk";
    std::string pancakeEnd = pancake;
    std::random_shuffle(pancake.begin(), pancake.end());
    int count = 0;
    int depth_limit = 1;
    std::string result;
    int f_limit = h4(pancake);
    while (result == "") {
        result = ida_star(pancake, pancakeEnd, depth_limit, count, f_limit);
        if (result == "")
            f_limit = depth_limit;
        depth_limit++;
    }
    std::cout << "Pancake: ";
    std::cout << pancake << std::endl;
    std::cout << std::endl;
    std::cout << "Pancake ordenado: ";
    std::cout << pancakeEnd << std::endl;
    std::cout << std::endl;
    if (result != "") {
        std::cout << "Pancake resuelto: " << result << std::endl;
    }
    else {
        std::cout << "No se encontro una solucion" << std::endl;
    }
    std::cout << "Nodos visitados: " << count << std::endl;
    return 0;
}

