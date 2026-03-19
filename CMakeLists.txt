cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(Editor VERSION 1.0.0)

add_executable(Editor
  "src/main.cpp"
  "src/Editor/Button.cpp"

  # These files will be added later
  # "src/Editor/Blocks.cpp"
  # "src/Editor/Level.cpp"
  # "src/Editor/Actor.cpp"
  # "src/Editor/ActorTooltip.cpp"
)

target_compile_definitions(
  Editor PUBLIC
  WITH_EDITOR
  CHECK_ERRORS
)

target_include_directories(
  Editor PUBLIC ${PROJECT_SOURCE_DIR}/src
)

set(SDLTTF_VENDORED ON)
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")
add_subdirectory(${VENDOR_DIR}/SDL)
add_subdirectory(${VENDOR_DIR}/SDL_image)
add_subdirectory(${VENDOR_DIR}/SDL_ttf)

target_link_libraries(Editor PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
)

set(AssetDirectory "${PROJECT_SOURCE_DIR}/Assets")
add_custom_command(
  TARGET Editor POST_BUILD
  COMMAND
  ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3::SDL3>"
    "$<TARGET_FILE:SDL3_image::SDL3_image>"
    "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>"
    "$<TARGET_FILE_DIR:Editor>"

  COMMAND
  ${CMAKE_COMMAND} -E copy_directory_if_different
    "${AssetDirectory}"
    "$<TARGET_FILE_DIR:Editor>/Assets"
  VERBATIM
)
