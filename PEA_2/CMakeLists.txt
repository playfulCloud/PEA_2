cmake_minimum_required(VERSION 3.24)
project(PEA_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_2 main.cpp PEA_2/Utils/Presentation/Menu.cpp PEA_2/Utils/Presentation/Menu.h PEA_2/Utils/Reader/FileReader.cpp PEA_2/Utils/Reader/FileReader.h PEA_2/Utils/Timer/TimeCounter.cpp PEA_2/Utils/Timer/TimeCounter.h PEA_2/Utils/CityMatrix/AdjacencyMatrix.cpp PEA_2/Utils/CityMatrix/AdjacencyMatrix.h PEA_2/Algorithms/TabuSearch/TabuSearchImplementation.cpp PEA_2/Algorithms/TabuSearch/TabuSearchImplementation.h PEA_2/Algorithms/TabuSearch/TabuSearchImplementation.h PEA_2/Algorithms/TabuSearch/TabuSearchImplementation.h PEA_2/Algorithms/SimulatedAnnealing/SimulatedAnnealing.cpp PEA_2/Algorithms/SimulatedAnnealing/SimulatedAnnealing.h)
