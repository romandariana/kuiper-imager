find_package(Qt6 6.4 REQUIRED COMPONENTS Core)

add_executable(kli main.cpp)

target_link_libraries(kli PRIVATE kuiper::kuiper Qt6::Core)

# Install rule for packaging (CPack DEB). libkuiper is a static lib baked into
# kli, so only the binary is installed. See top-level CMakeLists.txt.
include(GNUInstallDirs)
install(TARGETS kli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
