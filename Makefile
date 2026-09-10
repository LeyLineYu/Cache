# TODO: use environment variables (CXX FLAGS, CC, etc.)
COMPILER := g++

ARTIFACT_PATH := build
BINARY_PATH   := bin

SOURCE_PATH   := src

INCLUDE_FLAGS := -I $(SOURCE_PATH)/
LIBS          := -lm -lc

# Common defines
DEFINE_FLAGS  :=

# Debug exclusive defines
DEBUG_DEFINE_FLAGS := -D _DEBUG

# Release exclusive defines
RELEASE_DEFINE_FLAGS := -D NDEBUG

PROG_NAME     := cache
MAIN_TARGET   := $(BINARY_PATH)/$(PROG_NAME)
TODO_FILE     := TODO.txt

# Source files (src/ is autoappended)
SOURCES       := main.cpp
SOURCES       := $(patsubst %.cpp, $(SOURCE_PATH)/%.cpp, $(SOURCES))

# Simple patsubst that's used a few times
define to_object
  $(patsubst $(SOURCE_PATH)/%.cpp, $(ARTIFACT_PATH)/%.o, $(1))
endef

OBJECTS      := $(call to_object,$(SOURCES))
DEPENDENCIES := $(OBJECTS:.o=.d)

SANITIZER_FLAGS := -fsanitize=address,alignment,bool,bounds,enum,$\
		 		           float-cast-overflow,float-divide-by-zero,$\
				           integer-divide-by-zero,leak,nonnull-attribute,$\
				           null,object-size,return,returns-nonnull-attribute,$\
				           shift,signed-integer-overflow,undefined,$\
				           unreachable,vla-bound,vptr
# Debug exclusive flags
DEBUG_CXX_FLAGS := -ggdb3 -O0 \
                   -Wstack-protector -fstack-protector \
									 -fno-omit-frame-pointer \
									 $(SANITIZER_FLAGS)
# Release exclusive flags
RELEASE_CXX_FLAGS := -O3

# Common flags
CXX_FLAGS := -Wall -Wextra                                                  \
  				   -Waggressive-loop-optimizations                                \
  				   -Wmissing-declarations -Wcast-align -Wcast-qual                \
  				   -Wchar-subscripts                                              \
  				   -Wconversion  -Wempty-body                                     \
  				   -Wfloat-equal -Wformat-nonliteral -Wformat-security            \
  				   -Wformat-signedness -Wformat=2 -Winline -Wlogical-op           \
  				   -Wopenmp-simd                                                  \
  				   -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls         \
  				   -Wshadow -Wsign-conversion                                     \
  				   -Wstrict-overflow=2 -Wsuggest-attribute=noreturn               \
  				   -Wsuggest-final-methods -Wsuggest-final-types                  \
  				   -Wsync-nand                                                    \
  				   -Wundef -Wunreachable-code -Wunused -Wuseless-cast             \
  				   -Wvariadic-macros                                              \
  				   -Wno-missing-field-initializers -Wno-narrowing                 \
  				   -Wno-varargs -fstrict-overflow                                 \
  				   -Wstack-usage=8192 -pie -fPIE -Werror=vla

.PHONY: debug debug_prehook release

# Default debug target ('make' == 'make debug')
debug: debug_prehook build update_todo

debug_prehook:
	$(eval DEFINE_FLAGS += $(DEBUG_DEFINE_FLAGS))
	$(eval CXX_FLAGS    += $(DEBUG_CXX_FLAGS))
	@echo "!Debug compilation mode!"

# Release target (activated by running 'make release')
release: release_prehook build

release_prehook:
	$(eval DEFINE_FLAGS += $(RELEASE_DEFINE_FLAGS))
	$(eval CXX_FLAGS    += $(RELEASE_CXX_FLAGS))
	@echo "!Release compilation mode!"

build: ensure_directories_exist $(MAIN_TARGET)

$(MAIN_TARGET): $(OBJECTS)
	@echo -e "• Linking "$(MAIN_TARGET)" together"
	@$(COMPILER) $(CXX_FLAGS) $^ -o $@ $(LIBS)

# Include dependencies (object: headers + source file), if they exist
-include $(DEPENDENCIES)

# Implied rule for objects
$(ARTIFACT_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@echo -e "• Compiling" $<
	@mkdir -p $(@D)
	@$(COMPILER) -c -MMD $(DEFINE_FLAGS) \
	             $(INCLUDE_FLAGS) $(LIBS) $(CXX_FLAGS) $< -o $@

.PHONY: ensure_directories_exist clean build update_todo

ensure_directories_exist:
	mkdir -p $(BINARY_PATH) $(ARTIFACT_PATH)

clean:
	rm -f $(MAIN_TARGET)
	rm -f -r $(ARTIFACT_PATH)
	mkdir -p $(ARTIFACT_PATH)

update_todo:
	@echo -e "• Updating $(TODO_FILE)"
	@rm -f $(TODO_FILE)
	@grep -r -n "TODO" --exclude="Makefile" \
	                   --exclude=".gitignore" \
										 --exclude-dir=.git | sed G >> $(TODO_FILE)
