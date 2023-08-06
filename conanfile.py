#! /usr/bin/env python
# -*- coding: utf-8 -*-

from conan import ConanFile
from conan.tools.cmake import CMake


class ConanRecipt(ConanFile):
    name = 'LazyJson'

    settings = [
        'os',
        "compiler",
        'arch',
        'build_type',
    ]

    generators = [
        "CMakeToolchain", "CMakeDeps"
    ]

    def requirements(self) -> None:
        self.requires('gtest/1.14.0')

    def build(self) -> None:
        cmake: CMake = CMake(self)

        cmake.configure()
        cmake.build()
