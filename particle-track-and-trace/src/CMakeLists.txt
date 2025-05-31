cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(ParticleTrackTrace)

include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(VTK COMPONENTS
  GeovisCore
  CommonColor
  CommonCore
  CommonDataModel
  FiltersGeneral
  FiltersGeometry
  FiltersTexture
  FiltersProgrammable
  FiltersSources
  ImagingSources
  ImagingGeneral
  ImagingCore
  InteractionStyle
  IOImage
  RenderingContextOpenGL2
  RenderingCore
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2)


if (NOT VTK_FOUND)
  message(FATAL_ERROR "VtkBase: Unable to find the VTK build folder.")
endif()

# netcdf setup
# find_package(netCDF REQUIRED)

# include(FetchContent)
# FetchContent_Declare(SFML
#         GIT_REPOSITORY https://github.com/SFML/SFML.git
#         GIT_TAG 2.5.x
#         FIND_PACKAGE_ARGS NAMES SFML COMPONENTS system window audio main)
# FetchContent_MakeAvailable(SFML)

find_package(SFML COMPONENTS system window audio)

add_executable(ParticleTrackTrace MACOSX_BUNDLE main.cpp
        layers/BackgroundImage.cpp
        layers/BackgroundImage.h
        layers/EulerGlyphs.cpp
        layers/EulerGlyphs.h
        layers/Layer.cpp
        layers/Layer.h
        layers/LagrangeGlyphs.cpp
        layers/LagrangeGlyphs.h
        Program.cpp
        Program.h
        commands/TimerCallbackCommand.h
        commands/TimerCallbackCommand.cpp
        commands/SpawnPointCallback.h
        commands/SpawnPointCallback.cpp
        commands/CameraMoveCallback.cpp
        commands/CameraMoveCallback.h
        CartographicTransformation.cpp
        advection/kernel/AdvectionKernel.h
        advection/kernel/EulerAdvectionKernel.cpp
        advection/kernel/EulerAdvectionKernel.h
        advection/interpolate.cpp
        advection/interpolate.h
        advection/readdata.cpp
        advection/readdata.h
        advection/kernel/RK4AdvectionKernel.cpp
        advection/kernel/RK4AdvectionKernel.h
        advection/UVGrid.cpp
        advection/UVGrid.h
        advection/Vel.cpp
        advection/Vel.h
        advection/kernel/SnapBoundaryConditionKernel.h
        advection/kernel/SnapBoundaryConditionKernel.cpp
        layers/Character.h
        layers/Character.cpp
        commands/CharacterMoveCallback.h
        commands/CharacterMoveCallback.cpp
        layers/ParticleCollision.h
        layers/ParticleCollision.cpp
        collisions/ParticleCollisionCallback.h
        collisions/DummyCollisionHandler.h
        collisions/DummyCollisionHandler.cpp
        layers/Vessels.h
        layers/Vessels.cpp
        vesselroutes/VesselRoute.h
        vesselroutes/QuadraticBezierRoute.cpp
        vesselroutes/QuadraticBezierRoute.h
        vesselroutes/VesselRouteFactory.cpp
        vesselroutes/VesselRouteFactory.h
        layers/FoodSpawner.cpp
        layers/FoodSpawner.h
        collisions/ParticleRemover.cpp
        collisions/ParticleRemover.h
        vesselroutes/StraightLineRoute.cpp
        vesselroutes/StraightLineRoute.h
        layers/Health.cpp
        layers/Health.h
        layers/Health.h
        collisions/FoodPickup.cpp
        collisions/FoodPickup.h
        collisions/DebrisPickup.cpp
        collisions/DebrisPickup.h
        layers/Camera.cpp
        layers/Camera.h
        layers/GameOverScreen.cpp
        layers/GameOverScreen.h
        gameovers/GameoverCallback.h
        layers/Timer.cpp
        layers/Timer.h
        commands/DismissGameoverScreen.cpp
        commands/DismissGameoverScreen.h
        layers/DayCounter.cpp
        layers/DayCounter.h
        layers/Badges.cpp
        layers/Badges.h
        badges/Badge.h
        badges/Badge.cpp
        badges/StaticBadge.cpp
        badges/StaticBadge.h
        statistics/Statistic.h
        collisions/TrackedCollision.cpp
        collisions/TrackedCollision.h
        badges/Achievement.h
        badges/SimpleAchievement.cpp
        badges/SimpleAchievement.h
        badges/FileBadgeFactory.cpp
        badges/FileBadgeFactory.h
        layers/StatisticsManager.cpp
        layers/StatisticsManager.h
        statistics/Statistic.cpp
        layers/BadgeCounter.cpp
        layers/BadgeCounter.h
        layers/BadgeCounter.h
        statistics/BadgesAcquired.cpp
        statistics/BadgesAcquired.h
        badges/TrackedAchievement.cpp
        badges/TrackedAchievement.h
        commands/CharacterMouseMoveCallback.cpp
        commands/CharacterMouseMoveCallback.h
        layers/CharacterNoStop.h
        layers/CharacterNoStop.cpp
        collisions/SoundEffect.cpp
        collisions/SoundEffect.h
        layers/SplashScreen.cpp
        layers/SplashScreen.h
        commands/DisplaySplashScreenCommand.cpp
        commands/DisplaySplashScreenCommand.h
        commands/DisplayEulerCommand.cpp
        commands/DisplayEulerCommand.h
        commands/UserStudyTimer.h
        commands/UserStudyTimer.cpp
        layers/UserStudyTimerInitialiser.cpp
        layers/UserStudyTimerInitialiser.h
)

execute_process(
    COMMAND nc-config --includedir
    OUTPUT_VARIABLE netCDF_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ncxx4-config --prefix
    OUTPUT_VARIABLE NETCDFCXX_LIB_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_include_directories(ParticleTrackTrace PUBLIC ${netCDF_INCLUDE_DIR})

cmake_print_variables(netCDF_INCLUDE_DIR "${NETCDFCXX_LIB_DIR}/lib" NETCDF_LIB)

find_library(NETCDF_LIB NAMES netcdf-cxx4 netcdf_c++4 PATHS "${NETCDFCXX_LIB_DIR}/lib" NO_DEFAULT_PATH)

cmake_print_variables(netCDF_INCLUDE_DIR "${NETCDFCXX_LIB_DIR}/lib" NETCDF_LIB)

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
target_link_libraries(ParticleTrackTrace ${NETCDF_LIB} ${VTK_LIBRARIES} sfml-audio)

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ParticleTrackTrace
  MODULES ${VTK_LIBRARIES}
)

if(WIN32)
add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
