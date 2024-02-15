#!/bin/bash

# Compile the C program
gcc -o copy_file_dir copy_file_dir.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Creating test directories and files
mkdir -p testdir/subdir
echo "Hello World" > testdir/subdir/file1.txt
echo "Another file" > testdir/file2.txt
touch testfile.txt

# Define destination paths
dest1="testfile_copy.txt"
dest2="emptydir_copy"
dest3="testdir_copy"
dest4="testdir_with_subdir_copy"

# Test case 1: Copy a regular file
echo "Test case 1: Copying a regular file"
./filecopy testfile.txt $dest1
ls -l $dest1

# Test case 2: Copy an empty directory
echo "Test case 2: Copying an empty directory"
mkdir emptydir
./filecopy emptydir $dest2
ls -l $dest2

# Test case 3: Copy a directory with files
echo "Test case 3: Copying a directory with some files"
./filecopy testdir $dest3
ls -l $dest3

# Test case 4: Copy a directory with subdirectories and files
echo "Test case 4: Copying a directory with subdirectories and files"
mkdir -p testdir/subdir2
echo "File in subdir2" > testdir/subdir2/file3.txt
./filecopy testdir $dest4
ls -l $dest4



# Clean up after running .sh file 
# rm -r testdir emptydir testfile.txt $dest1 $dest2 $dest3 $dest4
