if (NOVA_FOUND)
ADD_EXECUTABLE( test_skypoint test_skypoint.cpp )
TARGET_LINK_LIBRARIES( test_skypoint ${TEST_LIBRARIES})
ADD_TEST( NAME TestSkyPoint COMMAND test_skypoint )
endif()
