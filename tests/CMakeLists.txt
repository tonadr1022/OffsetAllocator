add_executable(offset_allocator_tests
    main.cpp
)

target_link_libraries(offset_allocator_tests PRIVATE
    offsetAllocator
)
