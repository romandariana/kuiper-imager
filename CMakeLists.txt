cmake_minimum_required(VERSION 3.22)

project(kuiper-imager
    VERSION 2.0.0
    DESCRIPTION "ADI Kuiper Imager"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

option(KUIPER_IMAGER_GUI "Build the Qt Widgets GUI front-end" ON)
option(KUIPER_IMAGER_PACKAGE "Enable CPack packaging config (.deb)" OFF)

add_subdirectory(src/core)
add_subdirectory(src/cli)

if(KUIPER_IMAGER_GUI)
    add_subdirectory(src/gui)
endif()

message(STATUS "kuiper-imager ${PROJECT_VERSION} | GUI: ${KUIPER_IMAGER_GUI}")

# Packaging: native Debian package (CPack DEB generator). Off by default; the
# `deb-linux` preset turns it on. Built against the distro Qt (see the Qt floor
# note in src/core/CMakeLists.txt) so the package stays thin and depends on the
# distro's shared libraries. CLI-only for now — the GUI is not yet wired up, so
# there is no .desktop/icon to install. See plan.md §9.
if(KUIPER_IMAGER_PACKAGE)
    set(CPACK_PACKAGE_NAME "kuiper-imager-cli")
    set(CPACK_PACKAGE_VENDOR "Analog Devices")
    set(CPACK_PACKAGE_CONTACT "Alisa-Dariana Roman <alisa.roman@analog.com>")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION} (CLI)")
    set(CPACK_PACKAGE_DESCRIPTION
        "kli fetches, flashes, and configures Kuiper Linux images for Analog\nDevices hardware. This is the command-line front-end; it links the distro's\nQt 6 Core at runtime.")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    set(CPACK_STRIP_FILES ON)  # Release binaries; drop debug symbols from the .deb

    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
    set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE
        "https://github.com/analogdevicesinc/kuiper-imager")
    # Compute exact versioned Depends from the linked ELF (needs dpkg-shlibdeps),
    # rather than hardcoding a package list that drifts across distros.
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    # -> kuiper-imager-cli_2.0.0-1_amd64.deb
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

    include(CPack)
endif()
