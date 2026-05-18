# Minimalna wersja CMake
cmake_minimum_required(VERSION 3.20)

# Nazwa projektu
project(Projekt_QoS CXX)

# Wymuszenie C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# === KLUCZOWY BLOK: WYMUSZENIE TRYBU RELEASE ===
# Jeśli użytkownik nie podał typu buildu, brutalnie wymuś Release (-O3)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Domyślny tryb nie został wybrany. Wymuszam tryb: Release (Maksymalna wydajność)")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Typ builda (Release, Debug, etc.)" FORCE)
endif()
# =================================================

# Gdzie leżą pliki nagłówkowe
include_directories(include)

# Lista plików źródłowych
set(SOURCES
    src/main.cpp
    src/MaxHeap.cpp
    src/UnorderedArray.cpp
    src/DataGenerator.cpp
)

# Budujemy plik wykonywalny
add_executable(Projekt_QoS ${SOURCES})