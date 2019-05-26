# CMakeList.txt : CMake project for SimpleExpressionEvaluator, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (SimpleExpressionEvaluator "src/main.cpp" "src/VariableTable.cpp" "src/ExpressionEvaluator.cpp")

# TODO: Add tests and install targets if needed.
