My octave simulator

The program simulates the operations from Octave with matrices.

I used a collection of matrices, a triple pointer and a size matrix (number of matrices)x2 which retains the dimensions of the matrices: the number of lines and the number of columns.

The first function corresponds to the first operation L, to add a matrix to the end of the collection.

The matrix number increases by 1, we reallocate the collection and the size matrix and allocate the new matrix.

The size function corresponds to operation D, for determining dimensions. Here the dimension matrix is useful, for the k index matrix, we display the k line from the dimension matrix.

The display function corresponds to the display operation P. For the k-index matrix, we display the matrix from the k-index collection.

The reallocation function corresponds to operation C. We used 2 auxiliary vectors, v1 contains the index of the lines used for reallocation, and v2 contains the columns. I allocated an auxiliary matrix, building it according to v1 and v2. I release the original matrix and allocate it to the new dimensions, then equalize its elements with those in the original matrix and schi,b the values in the dimension matrix as well. Finally, the auxiliary matrix.

The multiplication function corresponds to the operation M. I read the indices m and n for the matrices used for multiplication. I check the multiplication conditions and if they are respected, the algorithm continues. I choose an auxiliary matrix that will retain the result. I reallocate the collection and the matrix of dimensions and finally add the new matrix obtained by multiplying the index matrices m and n.

I used two functions that exchange pointers to two matrices (swap_matrix), respectively to two vectors (swap_array), to make the sorting process easier.

The sum function returns the sum of the elements in the matrix of index k.

The sorting function corresponds to the operation O. I use the interchange algorithm. If a matrix with a lower index has a larger sum than another with a higher index, exchange the pointers of the matrices in the collection and in the dimensions matrix.

The multiply function is a function that calculates the multiplication of two matrices. I used this function to raise the power of a matrix.

The power function corresponds to the operation R. The algorithm has a logarithmic order execution time, using the state of the power, even or odd number. If the conditions for raising the power are met, the algorithm continues. I used an auxiliary matrix that I allocate and equalize with the original matrix. It does not retain the result, it is intermediate in the algorithm. The result is directly retained in the original matrix. Finally, I release the auxiliary matrix.

The tras put function corresponds to the operation T. I allocate an auxiliary matrix of the dimensions of the transpose and construct it. I release the original matrix and reallocate it to the transposed dimensions, then equalizing it with the auxiliary matrix. At the end, I release the auxiliary matrix and exchange the dimension values in the dimension matrix.

The release function corresponds to operation F. I move the index matrix k that I want to release to the end of the collection. Anyway, I reduce the number of matrices and reallocate the collection to the new size.

The output function corresponds to the Q operation where the entire collection is released.

For the bonus with multiplication using Strassen's algorithm, I used several functions. The add and subtract functions calculate the sum and subtraction of two matrices, respectively. Another function is for the allocation of quadratic matrices used in the Strassen algorithm.

The Strassen function is the algorithm itself. It is a recursive algorithm, where the basic case is when the size of the blocks is 1 when we keep dividing into submatrices. I used a collection of matrices, which contains the necessary matrices for the algorithm, the 7 (p) and for each matrix the 4 subdivision blocks and 2 more auxiliary ones for the calculation. I used a collection to make it easy to allocate each matrix and release it. Dim2 represents the new dimension after each recurrence.

The bonus function corresponds to the operation S. I check the conditions of the Strassen algorithm, reallocate the collection of matrices, adding a new matrix to its end that will hold the result of multiplying the two indicated matrices, then I perform Strassen on the two matrices.

In main I have an infinite loop where I read characters and a space. For each character I call the corresponding function. At the Q character I call the corresponding function and then break to exit the loop and end the program.
