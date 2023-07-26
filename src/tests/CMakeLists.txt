find_package(GTest REQUIRED)

set(TARGET
    lazy_json_tests
)

set(SOURCES
    main.cpp
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE GTest::GTest)

add_test(NAME ${TARGET}
    COMMAND ${TARGET}
)
