find_package(GTest REQUIRED)

set(TARGET
    lazy_json_tests
)

set(SOURCES
    main.cpp

    json.cpp
    variant.cpp
)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

set(INCLUDES
    ${PARENT_DIR}
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE GTest::GTest)
target_include_directories(${TARGET} PRIVATE ${INCLUDES})

add_test(NAME ${TARGET}
    COMMAND ${TARGET}
)
