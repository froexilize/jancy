#...............................................................................
#
#  This file is part of the Jancy toolkit.
#
#  Jancy is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/jancy/license.txt
#
#...............................................................................

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
	CMAKE_VERSION=3.3.2
	CMAKE_VERSION_DIR=v3.3
	CMAKE_OS=Linux-x86_64

	export CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
	export CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
	export CMAKE_DIR=$TRAVIS_BUILD_DIR/cmake-$CMAKE_VERSION
	export PATH=$CMAKE_DIR/bin:$PATH

	# lcov doesn't work with clang on ubuntu out-of-the-box
	# also, coverage should be collected without optimizations

	if [ "$CC" != "clang" ] && [ "$BUILD_CONFIGURATION" == "Debug" ]; then
		export GET_COVERAGE=ON
	fi

	if [ "$TARGET_CPU" == "amd64" ] && \
	   [ "$CC" == "gcc" ] && \
	   [ "$BUILD_CONFIGURATION" == "Release" ] &&\
	   [ "$LLVM_VERSION" == "3.4.2" ]; then
		export BUILD_DOC=ON
 	fi
fi
