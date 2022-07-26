cmake_minimum_required(VERSION 3.13)

project(lwm2munittests C)

add_compile_definitions(_POSIX_C_SOURCE=200809)

include(${CMAKE_CURRENT_LIST_DIR}/../core/wakaama.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../coap/coap.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../data/data.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../examples/shared/shared.cmake)

if(DTLS)
    list(REMOVE_ITEM SHARED_DEFINITIONS DTLS)
endif()

add_compile_definitions(SHARED_DEFINITIONS)
add_compile_definitions(LWM2M_CLIENT_MODE)
add_compile_definitions(LWM2M_SUPPORT_TLV)
add_compile_definitions(LWM2M_SUPPORT_JSON)

if(LWM2M_VERSION VERSION_GREATER "1.0")
    add_compile_definitions(LWM2M_SUPPORT_SENML_JSON)
endif()

# Enable all warnings for this test build  
add_compile_options(-pedantic -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default)

include_directories(${WAKAAMA_HEADERS_DIR} ${COAP_HEADERS_DIR} ${DATA_HEADERS_DIR} ${WAKAAMA_SOURCES_DIR} ${SHARED_INCLUDE_DIRS})
set_source_files_properties(${DATA_SOURCES_DIR}/senml_json.c PROPERTIES COMPILE_FLAGS -Wno-float-equal)

file(GLOB SOURCES "*.c")

add_executable(${PROJECT_NAME} ${SOURCES} ${WAKAAMA_SOURCES} ${COAP_SOURCES} ${DATA_SOURCES} ${SHARED_SOURCES})
target_link_libraries(${PROJECT_NAME} cunit)

if(SANITIZER)
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=${SANITIZER} -fno-sanitize-recover=all)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=${SANITIZER} -fno-sanitize-recover=all)
endif()

if(COVERAGE)
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
    target_link_options(${PROJECT_NAME} PRIVATE --coverage)
endif()

# Add our unit tests to it "test" target
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})
