cmake_minimum_required(VERSION 3.24)
project(PEA_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_1 main.cpp PEA_1/Utils/Presentation/Menu.cpp PEA_1/Utils/Presentation/Menu.h PEA_1/Utils/Reader/FileReader.cpp PEA_1/Utils/Reader/FileReader.h PEA_1/Utils/Timer/TimeCounter.cpp PEA_1/Utils/Timer/TimeCounter.h PEA_1/Algorithms/BruteForce/BruteForce_Implementation.cpp PEA_1/Algorithms/BruteForce/BruteForce_Implementation.h PEA_1/Algorithms/BranchAndBound/BranchAndBound_Implementation.cpp PEA_1/Algorithms/BranchAndBound/BranchAndBound_Implementation.h PEA_1/Algorithms/DynamicProgramming/DynamicProgramming_implementation.cpp PEA_1/Algorithms/DynamicProgramming/DynamicProgramming_implementation.h PEA_1/Utils/RandomGenerator/Generator.cpp PEA_1/Utils/RandomGenerator/Generator.h PEA_1/Utils/CityMatrix/Matrix.cpp PEA_1/Utils/CityMatrix/Matrix.h)
