# Vendored doctest (single-header, header-only test framework).
# Located at thirdparty/doctest/doctest/doctest.h, so the include base is
# thirdparty/doctest and tests use: #include <doctest/doctest.h>
add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE
    $<BUILD_INTERFACE:${UNITS_ROOT_DIR}/thirdparty/doctest>
)
add_library(GwUnits::doctest ALIAS doctest)
