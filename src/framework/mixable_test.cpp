#include <gtest/gtest.h>

#include "mixable.hpp"

#include <sstream>

using namespace std;

namespace jubatus {
namespace framework {

struct int_model {
  int value;

  void save(std::ostream & ofs) {
    ofs << value;
  }

  void load(std::istream & ifs) {
    ifs >> value;
  }
};

class mixable_int : public mixable<int_model, int> {
 public:
  void clear() {}
  int get_diff_impl() const { return 0; }
  void put_diff_impl(const int& n) {}
  void reduce_impl(const int& diff, int& acc) const {}
};

TEST(mixable, config_not_set) {
  mixable_int m;
  EXPECT_THROW(m.get_diff(), config_not_set);
  EXPECT_THROW(m.put_diff(""), config_not_set);
}

TEST(mixable, save_load) {
  mixable_int m;
  m.set_model(mixable_int::model_ptr(new int_model));
  m.get_model()->value = 10;

  stringstream ss;
  m.save(ss);
  m.get_model()->value = 5;
  m.load(ss);
  EXPECT_EQ(10, m.get_model()->value);
}

}
}
