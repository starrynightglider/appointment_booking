CXX := g++
CPPFLAGS := -I. -Isubmodule/rapidjson/include -Isubmodule/gtest/googletest/include
CXXFLAGS := -std=c++17
BUILD := build
OBJ := obj
TEST_BUILD := test_build
LIBS := -lgtest
LDFLAGS := -Lsubmodule/gtest/build/lib 
DEPENDENCIES = \
	submodule/rapidjson/readme.md \
	submodule/gtest/build/lib/libgtest.a
HEADERS := \
	order.hpp\
	util.hpp\
	booking.hpp
OBJFILES := \
	$(OBJ)/order.o \
	$(OBJ)/booking.o 

main:  $(DEPENDENCIES) $(HEADERS) $(OBJFILES) $(OBJ)/main.o	
	@mkdir -p $(BUILD)
	$(CXX) -o $(BUILD)/$@ $(OBJ)/main.o $(OBJFILES) $(CXXFLAGS) $(CPPFLAGS) $(LIBS) $(LDFLAGS)

$(OBJ)/main.o: main.cpp $(HEADERS)
	@mkdir -p $(OBJ)
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

$(OBJ)/order.o: order.cpp $(HEADERS)
	@mkdir -p $(OBJ)
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

$(OBJ)/booking.o: booking.cpp $(HEADERS)
	@mkdir -p $(OBJ)
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

test: tests/test_booking.cpp $(DEPENDENCIES) $(HEADERS)
	@mkdir -p $(TEST_BUILD)
	$(CXX) $< -o $(TEST_BUILD)/$@.out $(OBJFILES) $(CXXFLAGS) $(CPPFLAGS) $(LIBS) $(LDFLAGS)

run_test: main test
	$(TEST_BUILD)/test.out

clean: 
	@rm -rf $(BUILD) $(OBJ) $(TEST_BUILD)

submodule/rapidjson/readme.md:
	@echo Cannot find rapidjson submodule, did you use --recursive in git clone? && exit 1

submodule/gtest/build/lib/libgtest.a:
	@echo Attempting to build gtest ...
	cd submodule/gtest; mkdir -p build; cd build; cmake ..; make

