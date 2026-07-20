BUILD_DIR = build
TARGET_VERSION = 122
TARGET_NAME = 5bw_$(TARGET_VERSION)
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

ifeq ($(OS),Windows_NT)
    # Windows
    CHECK_PROG = powershell -NoProfile -Command "if (-not (Get-Command $(1) -ErrorAction SilentlyContinue)) { Write-Error \"Could not find '$(1)', please install it.\"; exit 1 }"
    FORMAT_CMD = powershell -NoProfile -Command "Get-ChildItem -Path . -Recurse -Depth 2 | Where-Object { $$_.Extension -in '.cpp','.h','.hpp' } | ForEach-Object { clang-format -i $$_.FullName }"
    RUN_CMD = $(TARGET).exe
else
    # UNIX / MACOS
    CHECK_PROG = $(if $(shell which $(1) 2>/dev/null),,$(error Could not find '$(1)', please install it.))
    FORMAT_CMD = clang-format -i main.cpp $$(find . -maxdepth 3 -name "*.cpp" -o -name "*.h" -o -name "*.hpp")
    RUN_CMD = ./$(TARGET)
endif

all: check_cmake build run

check_cmake:
	$(call CHECK_PROG,cmake)

check_cf:
	$(call CHECK_PROG,clang-format)

build:
	cmake -S . -B $(BUILD_DIR) -DTARGET_NAME=$(TARGET_NAME)
	cmake --build $(BUILD_DIR)

run:
	$(RUN_CMD)

format: check_cf
	$(FORMAT_CMD)

.PHONY: all check_cmake check_cf build run format