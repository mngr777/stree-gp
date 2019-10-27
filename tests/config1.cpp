#include <iostream>
#include <streegp/streegp.hpp>

int main() {
    using namespace std;
    using namespace stree;

    gp::Config config = gp::make_default_config();
    cout << config << endl;

    return 0;
}
