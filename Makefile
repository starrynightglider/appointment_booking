CXX := g++
CPPFLAGS := -I. -Isubmodule/rapidjson/include
CXXFLAGS := -std=c++17
BUILD := build
COMPILE = @echo CXX $@ && $(CXX) $(CXXFLAGS) $? -o $@ $(CPPFLAGS)

DEPENDENCIES = \
	submodule/rapidjson/readme.md

main: main.cpp $(DEPENDENCIES)
	@mkdir -p $(BUILD)
	$(CXX) $< -o $(BUILD)/$@.out $(CXXFLAGS) $(CPPFLAGS)

clean: 
	@rm -rf $(BUILD)

submodule/rapidjson/readme.md:
	@echo rapidjson submodule does not seem to exists, did you use --recursive in git clone? && exit 1


