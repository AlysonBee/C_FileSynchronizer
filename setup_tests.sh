rm -r -v  tests/folder1/file2.txt tests/folder1/file3.txt tests/folder1/file4.txt
rm -r -v tests/folder2/file1.txt tests/folder2/file3.txt tests/folder2/file4.txt
rm -r -v tests/folder3/file1.txt tests/folder3/file2.txt tests/folder3/file4.txt
rm -r -v tests/folder4/file1.txt tests/folder4/file2.txt tests/folder4/file3.txt

cp -v synchronize tests/folder1
cp -v synchronize tests/folder2
cp -v synchronize tests/folder3
cp -v synchronize tests/folder4
