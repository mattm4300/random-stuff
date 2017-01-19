echo "Copying sll and integer"
cd ./sll/
cp integer.c ./../testdir/
cp integer.h ./../testdir/
cp sll.h ./../testdir/
cp sll.c ./../testdir/
cd ..

echo "copying dll"
cd ./dll/
cp dll.h ./../testdir/
cp dll.c ./../testdir/
cd ..

echo "copying stack"
cd ./stack/
cp stack.h ./../testdir/
cp stack.c ./../testdir/
cd ..

echo "copying queue"
cd ./queue/
cp queue.c ./../testdir/
cp queue.h ./../testdir/
cd ..

echo "Done"
