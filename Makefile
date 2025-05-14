.PHONY: gen build run fmt clean fclean
.DEFAULT_GOAL := build

CMAKE_CFG ?= macos
CMAKE_REL ?= debug

CMAKE_ARGS = --preset $(CMAKE_CFG)-$(CMAKE_REL)
BUILD_DIR = out

gen: ## generate cmake build files
	cmake --preset $(CMAKE_CFG)

build: ## build project
	cmake --build $(CMAKE_ARGS)

# todo: case sensitive cmake_rel dir and relDebug -> RelWithDebInfo
run: build ## run project
	./$(BUILD_DIR)/build/$(CMAKE_CFG)/sources/game/$(CMAKE_REL)/game

clean: ## remove cmake build artifacts
	cmake --build $(CMAKE_ARGS) --target clean

fclean: ## full clean build dir
	rm -rf $(BUILD_DIR)
