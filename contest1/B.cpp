#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr int kPrecision = 10;

void CalcPrefixProductLog(const std::vector<double>& arr,
                          std::vector<long double>& pref_prod_log) {
  pref_prod_log.resize(arr.size() + 1);
  pref_prod_log[0] = 0;
  for (int i = 0; i < arr.size(); ++i) {
    pref_prod_log[i + 1] = pref_prod_log[i] + log(arr[i]);
  }
}

double CalcAns(std::vector<long double>& pref_prod_log, int left, int right) {
  return exp((pref_prod_log[right + 1] - pref_prod_log[left]) / (right - left + 1));
}

int main() {
  int number_of_mandrakes;
  std::cin >> number_of_mandrakes;
  std::vector<double> mandrakes_loudness(number_of_mandrakes);
  for (int i = 0; i < number_of_mandrakes; ++i) {
    std::cin >> mandrakes_loudness[i];
  }
  std::vector<long double> prefix_product_log;

  CalcPrefixProductLog(mandrakes_loudness, prefix_product_log);
  
  int number_of_requests;
  std::cin >> number_of_requests;
  int left;
  int right;
  std::cout << std::setprecision(kPrecision) << std::fixed;
  while (number_of_requests-- > 0) {
    std::cin >> left >> right;
    std::cout << CalcAns(prefix_product_log, left, right) << '\n';
  }

  return 0;
}