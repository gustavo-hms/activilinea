project(act-rename)
find_package(KDE4 REQUIRED)
find_package(KActivities REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${KACTIVITIES_INCLUDE_DIRS})
set(SRC_LIST act-rename.cpp)
kde4_add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(act-rename ${KDE4_KDEUI_LIBS} ${KACTIVITIES_LIBRARIES})
install(TARGETS act-rename ${INSTALL_TARGETS_DEFAULT_ARGS})
