    The first and the second function are basic structure operation.
    The addelement function:
   1.When the new element is already the sam with the old element, we just use return.
   2.The condition: set->card % INITSETSIZE == 0, equals to that the memory is full.
   3.Divide into three kinds to writ the program: int char double.

    The delete element function:
   1.Initialize a new pointer *new to present the pointer after delete an element, 
      and then replicate the set->elem with new.