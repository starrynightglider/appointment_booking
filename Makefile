CXX := g++
CPPFLAGS := -I. -Isubmodule/rapidjson/include -Isubmodule/gtest/googletest/include/
CXXFLAGS := -std=c++17
BUILD := build
TEST_BUILD := test_build
LIBS := -lgtest
LDFLAGS := -Lsubmodule/gtest/build/lib 
DEPENDENCIES = \
	submodule/rapidjson/readme.md \
	submodule/gtest/build/lib/libgtest.a

main: main.cpp $(DEPENDENCIES)
	@mkdir -p $(BUILD)
	$(CXX) $< -o $(BUILD)/$@.out $(CXXFLAGS) $(CPPFLAGS) $(LIBS) $(LDFLAGS)

test: tests/parse_json.cpp
	@mkdir -p $(TEST_BUILD)
	$(CXX) $< -o $(TEST_BUILD)/$@.out $(CXXFLAGS) $(CPPFLAGS) $(LIBS) $(LDFLAGS)

run_test: test main
	$(TEST_BUILD)/test.out

clean: 
	@rm -rf $(BUILD) $(TEST_BUILD)

submodule/rapidjson/readme.md:
	@echo Cannot find rapidjson submodule, did you use --recursive in git clone? && exit 1

submodule/gtest/build/lib/libgtest.a:
	@echo Attempting to build gtest ...
	cd submodule/gtest; mkdir -p build; cd build; cmake ..; make

