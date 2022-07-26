cmake_minimum_required(VERSION 3.13)

project(lwm2mserver C)

include(${CMAKE_CURRENT_LIST_DIR}/../../core/wakaama.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../coap/coap.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../data/data.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../shared/shared.cmake)

if(DTLS)
    message(STATUS "server does not support DTLS")
    list(REMOVE_ITEM SHARED_DEFINITIONS DTLS)
endif()

add_compile_definitions(SHARED_DEFINITIONS)
add_compile_definitions(LWM2M_SERVER_MODE)

include_directories(${WAKAAMA_HEADERS_DIR} ${COAP_HEADERS_DIR} ${DATA_HEADERS_DIR} ${WAKAAMA_SOURCES_DIR} ${SHARED_INCLUDE_DIRS})

SET(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/lwm2mserver.c
)

add_executable(${PROJECT_NAME} ${SOURCES} ${WAKAAMA_SOURCES} ${COAP_SOURCES} ${DATA_SOURCES} ${SHARED_SOURCES})

SOURCE_GROUP(wakaama FILES ${WAKAAMA_SOURCES})
