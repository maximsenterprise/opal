
@include("iostream")

[typename T]
proc println(val as T&) {
	!cpp {
		std::cout << val << std::endl;
	}
}

method readline() : string {
	res out<string>;
	!cpp {
		std::cin >> out;	
	}
	give out;
}
