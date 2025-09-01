tar -cvf opendx.tar -C build opendx
cd build
cpack -G DEB
cd ..
mv build/opendx*.deb ./opendx.deb
