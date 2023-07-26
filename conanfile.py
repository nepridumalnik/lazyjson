#! /usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake


class QtTest(ConanFile):
    name = 'QtTest'

    settings = [
        'os',
        'build_type',
        'arch',
        'build_type',
    ]

    generators = [
        'cmake_find_package',
    ]

    def requirements(self) -> None:
        self.requires('gtest/[,include_prerelease=True]')

    def build(self) -> None:
        cmake: CMake = CMake(self)

        cmake.configure()
        cmake.build()
