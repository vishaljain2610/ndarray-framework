!Allocates contiguous chunk of memory and returns pointer to allocated memory
FUNCTION create_ndarray(size)
	INTEGER size
	real, dimension( : ),  pointer :: create_ndarray
	REAL, DIMENSION(:), ALLOCATABLE, TARGET :: aR
	INTEGER :: i
 	print *, "Heyyyy!"
	
	ALLOCATE(aR(size))
	aR(1) = 5
	aR(2) = 3

	do i = 1, 2
  		print *, aR(i)
	end do

	create_ndarray => aR
	print *, "Done!"
	RETURN
END FUNCTION


PROGRAM ndarray

	INTERFACE
		FUNCTION create_ndarray(size)
			INTEGER size
       		real, dimension( : ),  pointer :: create_ndarray
     	END FUNCTION
   	END INTERFACE
    
    real, dimension(:), pointer :: p

    p => create_ndarray(3)

END PROGRAM