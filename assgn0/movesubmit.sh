# from from source folders
sh ./movetest.sh

cd ./SUBMIT/
rm *
cd ..

cd ./testdir/

echo "Moving files to submit folder."

cp * ./../SUBMIT/
cd ./../SUBMIT/
make clean

echo "done"
