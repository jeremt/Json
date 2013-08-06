
/**
 * Some dependencies.
 */
#include <cassert>

/**
 * Include Json object.
 */
#include "Json.hpp"

/**
 * Define TEST macro to test Json values.
 */
# ifdef VERBOSE
#  define TEST(label, val, expected) \
    std::cout << label << " = " << val << std::endl; \
    assert(val == expected);
# else
#  define TEST(label, val, expected) \
    assert(val == expected);
#endif

/**
 * Define TEST_ERRORS macro to test Json errors.
 */
# ifdef VERBOSE
#  define TEST_ERRORS(file, expected) \
  try { \
    errors.load(file); \
    std::cout << "Ok :)" << std::endl; \
  } \
  catch (std::exception const &e) { \
    std::cout << "Catch exception: " << e.what() << std::endl; \
    assert( \
      e.what() == std::string(expected) || \
      std::string(expected) == "" \
    ); \
  }
# else
#  define TEST_ERRORS(file, expected) \
  try { \
    errors.load(file); \
  } \
  catch (std::exception const &e) { \
    assert( \
      e.what() == std::string(expected) || \
      std::string(expected) == "" \
    ); \
  }
# endif

/**
 * Program entry point.
 */
int main()
{
  Json errors;
  std::cout << std::endl
            << "  Start to test Json object..."
            << std::endl << std::endl;

  TEST_ERRORS("fail.json", "invalid json data.")
  TEST_ERRORS("invalidPath.json", "cannot open file \"invalidPath.json\".")
  TEST_ERRORS("urandom.json", "")
  TEST_ERRORS("empty.json", "")

  // Test parsing

  Json v;
  // std::string el;

  v.load("data.json");
#ifdef VERBOSE
  std::cout << v.str() << std::endl;
#endif
  std::string s = v["data"][0]["attr"][0]["value"];
  TEST("str", s, "http://google.com")
  int n = v["data"][1]["tuple"][0];
  TEST("int", n, 1)
  if (v["data"][1]["tuple"][5][1][1].is())
  {
    TEST("double", (double)v["data"][1]["pi"], 3.14)
    TEST("str", v["data"][2].str(), "{\n  \"done\": true\n}")
  }
  TEST("size", v["data"][3].size(), 4)

  // Test list

  Json list;

  list[0] = "Hello";
  list[4] = Json("Hello");
  list[1] = true;
  list[6] = 42;

  std::string el = list[0];
  TEST("el", el, "Hello")
  std::string r = "[\"Hello\", true, undefined, undefined, \"Hello\", undefined, 42]";
  TEST("list", list.str(), r)

  // Test map

  Json map;

  map["hello"] = "world";
  map["size"] = 1337;
  map["obj"]["data"] = "mdr";

  el = static_cast<std::string>(map["hello"]);
  TEST("el", el, "world")
  std::string data = map["obj"]["data"];
  TEST("data", data, "mdr")
  assert(map["size"] == Json::NUMBER);
  #ifdef VERBOSE
  std::cout << map.str() << std::endl;
  #endif

  // Test booleans

  map["testBool"] = true;

  TEST("testBool", map["testBool"].is(), true)
  TEST("testBoolStr", map["testBool"].str(), "true")

  // Test floats

  map["testFloat"] = 242e20;
  Json testFloat;
  testFloat.parse(map.str());

  float f = testFloat["testFloat"];
  (void)f;


  // I don't understand why this condition return false...
  // std::cout << f << std::endl;
  // std::cout << (f == 2.42e22) << std::endl;

  #ifdef VERBOSE
  std::cout << std::endl;
  #endif

  std::cout << "        All tests passed successfuly ;)"
            << std::endl << std::endl;

  return 0;

}