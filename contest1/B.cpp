#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr int kPrecision = 10;

int main() {
  int number_of_mandrakes;
  std::cin >> number_of_mandrakes;
  std::vector<double> mandrakes_loudness(number_of_mandrakes);
  for (int i = 0; i < number_of_mandrakes; ++i) {
    std::cin >> mandrakes_loudness[i];
  }
  std::vector<long double> prefix_product_log(number_of_mandrakes + 1);
  prefix_product_log[0] = 0;
  for (int i = 0; i < number_of_mandrakes; ++i) {
    prefix_product_log[i + 1] =
        prefix_product_log[i] + log(mandrakes_loudness[i]);
  }
  int number_of_requests;
  std::cin >> number_of_requests;
  int left;
  int right;
  std::cout << std::setprecision(kPrecision) << std::fixed;
  while (number_of_requests-- > 0) {
    std::cin >> left >> right;
    std::cout << exp((prefix_product_log[right + 1] -
                      prefix_product_log[left]) /
                     (right - left + 1))
              << '\n';
  }

  return 0;
}