project(act-ln)
find_package(KDE4 REQUIRED)
find_package(KActivities REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${KACTIVITIES_INCLUDE_DIRS})
set(SRC_LIST act-ln.cpp)
kde4_add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(act-ln ${KDE4_KDEUI_LIBS} ${KACTIVITIES_LIBRARIES})
install(TARGETS act-ln ${INSTALL_TARGETS_DEFAULT_ARGS})
