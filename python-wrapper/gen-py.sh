sed -i "s/\.\.\/include/\.\/include/g" $1
pushd .
cd ..
o=${1/.py/_py.cc} 
rm ./python-wrapper/$o
python ./python-wrapper/$1
popd 
sed -i "s/\"include/\"\.\.\/include/g" $o
python ./fix-pyplusplus.py $o > $o.bak
mv $o.bak $o
