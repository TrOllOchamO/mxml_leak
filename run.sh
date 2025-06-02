rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)
cp compile_commands.json ../compile_commands.json
cd src/
cp ../../*.xml ./
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
