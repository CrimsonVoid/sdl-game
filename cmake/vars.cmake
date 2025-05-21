# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(MSVC_WARNINGS
  /W4 # Baseline reasonable warnings
  /w14242 # 'identifier': conversion from 'type1' to 'type2', possible loss of data
  /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
  /w14263 # 'function': member function does not override any base class virtual member function
  /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
          # be destructed correctly
  /w14287 # 'operator': unsigned/negative constant mismatch
  /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
          # the for-loop scope
  /w14296 # 'operator': expression is always 'boolean_value'
  /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
  /w14545 # expression before comma evaluates to a function which is missing an argument list
  /w14546 # function call before comma missing argument list
  /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
  /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
  /w14555 # expression has no effect; expected expression with side- effect
  /w14619 # pragma warning: there is no warning number 'number'
  /w14640 # Enable warning on thread un-safe static member initialization
  /w14826 # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
  /w14905 # wide string literal cast to 'LPSTR'
  /w14906 # string literal cast to 'LPWSTR'
  /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
)

set(MSVC_DEFINITIONS
  _MSVC_STL_HARDENING=1
  _MSVC_STL_DESTRUCTOR_TOMBSTONES=1
)

set(CLANG_WARNINGS
  -Wall
  -Wextra # reasonable and standard
  -Wshadow # warn the user if a variable declaration shadows one from a parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
  # catch hard to track down memory errors
  -Wold-style-cast # warn for c-style casts
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual function
  -Wpedantic # warn if non-standard C++ is used
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  -Wnull-dereference # warn if a null dereference is detected
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output (ie printf)
  -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
)

set(CLANG_DEFINITIONS "")

set(PROJECT_CXX_WARNINGS
  $<$<CXX_COMPILER_ID:MSVC>:${MSVC_WARNINGS}>
  $<$<CXX_COMPILER_ID:GNU>:${CLANG_WARNINGS}>
  $<$<CXX_COMPILER_ID:Clang>:${CLANG_WARNINGS}>
  $<$<CXX_COMPILER_ID:AppleClang>:${CLANG_WARNINGS}>
)

set(PROJECT_CXX_DEFINITIONS
  $<$<CXX_COMPILER_ID:MSVC>:${MSVC_DEFINITIONS}>
  $<$<CXX_COMPILER_ID:GNU>:${CLANG_DEFINITIONS}>
  $<$<CXX_COMPILER_ID:Clang>:${CLANG_DEFINITIONS}>
  $<$<CXX_COMPILER_ID:AppleClang>:${CLANG_DEFINITIONS}>
)

macro(set_project_cxx_properties tgt)
  target_compile_features(${tgt} PRIVATE cxx_std_23)
  target_compile_options(${tgt} PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_CXX_OPTIONS}>)
  target_compile_definitions(${tgt} PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_CXX_DEFINITIONS}>)
  set_target_properties(${tgt} PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)
endmacro()