CXX := g++
CPPFLAGS := -I. -Isubmodule/rapidjson/include
CXXFLAGS := -std=c++17
BUILD := build
COMPILE = @echo CXX $@ && $(CXX) $(CXXFLAGS) $? -o $@ $(CPPFLAGS)

DEPENDENCIES = \
	submodule/rapidjson/readme.md \
	submodule/gtest/build/lib/libgtest.a

main: main.cpp $(DEPENDENCIES)
	@mkdir -p $(BUILD)
	$(CXX) $< -o $(BUILD)/$@.out $(CXXFLAGS) $(CPPFLAGS)

clean: 
	@rm -rf $(BUILD)

submodule/rapidjson/readme.md:
	@echo Cannot find rapidjson submodule, did you use --recursive in git clone? && exit 1

submodule/gtest/build/lib/libgtest.a:
	@echo Attempting to build gtest ...
	cd submodule/gtest; mkdir -p build; cd build; cmake ..; make

