
@include("iostream")

[typename T]
proc out(val as T&) {
	!cpp {
		std::cout << val << std::endl;
	}
}

method main() : int {
	out("Hello, World!");
	give 0;
}
