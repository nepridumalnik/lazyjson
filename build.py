#! /usr/bin/env python
# -*- coding: utf-8 -*-

import os

platform_name : str = "windows" if os.name == "Windows" else "linux"

current_dir : str = os.getcwd()

if not os.path.exists("build"):
    os.mkdir("build")

profile : str = os.path.join(current_dir, 'profiles', platform_name)

os.system("conan profile detect")
os.system(f'conan install . --output-folder=build -s build_type=Debug --build missing') #-pr:h {profile} -pr:b {profile} -s build_type=Debug
os.system(f'conan build . --output-folder=build -s build_type=Debug') #-pr:h {profile} -pr:b {profile}