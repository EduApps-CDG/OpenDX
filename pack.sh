tar -cvf opendx.tar -C build opendx
cd build
cpack
cd ..
mv build/opendx*.deb ./opendx.deb
