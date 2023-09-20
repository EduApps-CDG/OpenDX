tar -cvf opendx.tar -C build/root .
cd build
cpack
cd ..
mv build/opendx*.deb ./opendx.deb
