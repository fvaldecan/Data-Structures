#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
int exp(int x, int n);
int g(int k);
std::vector <std::string> Gray(int n);
int main(){
    int x;
    int n;
    std::cin >> x;
    int a = g(x);

    std::cout << a;
    return 0;
}
int exp(int x, int n){
    if(n == 0)
        return 1;
    if(n == 1)
        return x;
    if(n % 2 == 0)
        return exp(x * x, n / 2);
    return x * exp(x * x, (n - 1) / 2);
}

int g(int k) {
    if (k == 0)
        return 0;
    else if (k % 2 == 0)
        return g(k/2) + 1;
    else
        return g((k - 1)/ 2) + 2;
}
std::vector<std::string> Gray(int n){
    if (n == 1) {
        std::vector <std::string> base;
        base.push_back("0");
        base.push_back("1");
        return base;
    }
    if (n > 1) {
        std::vector<std::string>uv;
        std::vector<std::string>u = Gray(n - 1);
        for(int i = 0; i < u.size(); i++)
            u[i] += "1";

        std::reverse(u.begin(), u.end());
        std::vector<std::string>v = Gray(n - 1);
        for(int i = 0; i < v.size(); i++)
            v[i] += "0";

        uv.reserve(v.size()+ u.size());
        uv.insert( uv.end(), v.begin(), v.end() );
        uv.insert( uv.end(), u.begin(), u.end() );
        return uv;
    }

}
