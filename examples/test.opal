
-- Given an input nums and a target we have to return the indices that make that number

method main() : int {
	println(make_indices([1, 2, 3, 4, 5], 8));
	give 0;
}

method make_indices(input as list:int, target as int) : tuple:int {
	iter (input) { num in
		iter (input) { second in
			if ((num + second) == target) {
				give new tuple:int(list.get_index(num), list.get_index(second));
			}
			else {
				continue;
			}
		}
	}
	@error("Invalid endpoint")	
}
