# mari
#1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {

    int n, x, i = 0;
    bool d = true;
    vector <int>a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        a.push_back(x);
    }while
        (d && i < n)
        for (int j = 0; j < n - 1 - i; j++) {
            d = false;
            if (a[j] > a[j + 1]) {
                d = true;
                swap(a[j], a[j + 1]);
            }
        }

    i++;
    for (auto& s : a) {
        cout << s << " ";
    }

    return 0;
}

