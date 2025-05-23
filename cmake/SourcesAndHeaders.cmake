set(sources
    src/tmp.cpp
	src/body.cpp
	src/simulator.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/physic_engine/tmp.hpp
)

set(test_sources
  src/tmp_test.cpp
)
