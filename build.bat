echo off

mkdir %~dp0build
cd %~dp0build

conan install .. -pr ..\profiles\windows -s build_type=Debug --build=missing
conan build ..

cd %~dp0