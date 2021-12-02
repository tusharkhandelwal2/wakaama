# Provides SHARED_SOURCES_DIR, SHARED_SOURCES, SHARED_INCLUDE_DIRS and SHARED_DEFINITIONS variables

set(SHARED_SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR})

set(SHARED_SOURCES 
    ${SHARED_SOURCES_DIR}/commandline.c
    ${SHARED_SOURCES_DIR}/platform.c
    ${SHARED_SOURCES_DIR}/memtrace.c
)

set(SHARED_DEFINITIONS "")

if(DTLS_TINYDTLS)

    list(APPEND SHARED_SOURCES ${SHARED_SOURCES_DIR}/tinydtlsconnection.c)

    list(APPEND SHARED_DEFINITIONS WITH_TINYDTLS)
    list(APPEND SHARED_DEFINITIONS DTLS)

elseif(DTLS_MBEDTLS)

    list(APPEND SHARED_SOURCES ${SHARED_SOURCES_DIR}/mbedtlsconnection.c)

    list(APPEND SHARED_DEFINITIONS WITH_MBEDTLS)
    list(APPEND SHARED_DEFINITIONS DTLS)
endif()

set(SHARED_INCLUDE_DIRS ${SHARED_SOURCES_DIR})


set(SHARED_SOURCES
    ${SHARED_SOURCES}
    ${SHARED_SOURCES_DIR}/connection.c
    ${SHARED_SOURCES_DIR}/object_utils.c
    ${SHARED_SOURCES_DIR}/sec_context.c
)

