#define _USE_MATH_DEFINES
#include <cmath>

#include "../Operators/Operator.h"

class Cos : public Function {
public:
  double operator()() const override { return std::cos((args[0] * M_PI) / 180.0); }
  std::string getName() const override { return "cos"; }
  std::string getDescription() const override { return "cos(deg)"; }

  size_t getnArgs() const override { return 1; }
  void setArg(size_t narg, double arg) override { args[narg] = arg; }
private:
  double args[1] = { 0 };
};

extern "C" __declspec(dllexport) 
Operator * create() {
  return new Cos();
}