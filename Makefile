.PHONY: gen build run fmt clean fclean
.DEFAULT_GOAL := build

CMAKE_PRESET ?= macos-debug

CMAKE_ARGS = --preset $(CMAKE_PRESET)
BUILD_DIR = out

gen: ## generate cmake build files
	cmake $(CMAKE_ARGS)

build: ## build project
	cmake --build $(CMAKE_ARGS)

run: build ## run project
	./$(BUILD_DIR)/build/$(CMAKE_PRESET)/sources/game/game

clean: ## remove cmake build artifacts
	cmake --build $(CMAKE_ARGS) --target clean

fclean: ## full clean build dir
	rm -rf $(BUILD_DIR)

