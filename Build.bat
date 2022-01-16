@echo off
pushd %~dp0

pushd src
g++ main.cpp -o main.a
if %errorlevel% neq 0 goto noRun
.\main.a
:noRun
popd

popd