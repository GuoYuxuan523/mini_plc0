#include "catch2/catch.hpp"

#include "instruction/instruction.h"
#include "tokenizer/tokenizer.h"
#include "analyser/analyser.h"

#include <sstream>
#include <vector>
/*
	不要忘记写测试用例喔。
*/
TEST_CASE("Test hello world1.") {

	std::string input =
		"begin\n"
		"	const a = 2266"
		"	var b = -2147483647;\n"
		"	var c = 123;\n"
		"	var d = 234;\n"
		"	b = 3;\n"
		"	print(a+b+c+d+e);\n"
		"end\n";
	std::stringstream ss;
	ss.str(input);
	miniplc0::Tokenizer tkz(ss);
	std::vector<miniplc0::Token> output = {};
	auto result = tkz.AllTokens();
	if (result.second.has_value()) {
		FAIL();
	}
	for (auto i : result.first) {
		std::cout << i.GetType() << '\t' << "start " << i.GetStartPos().first << '\t' << i.GetStartPos().second \
			<< "\tend " << i.GetEndPos().first << '\t' << i.GetEndPos().second << '\t' << i.GetValueString() << std::endl;
	}
	miniplc0::Analyser anl(result.first);
	auto result1 = anl.Analyse();
	for (auto j : result1.first) {
		if(j.GetOperation()==1)
			std::cout << "LIT" << '\t' << j.GetX() << std::endl;
		else if (j.GetOperation() == 2)
			std::cout << "LOD" << '\t' << j.GetX() << std::endl;
		else if (j.GetOperation() == 3)
			std::cout << "STO" << '\t' << j.GetX() << std::endl;
		else if (j.GetOperation() == 4)
			std::cout << "ADD" << std::endl;
		else if (j.GetOperation() == 5)
			std::cout << "SUB" << std::endl;
		else if (j.GetOperation() == 6)
			std::cout << "MUL" << std::endl;
		else if (j.GetOperation() == 7)
			std::cout << "DIV" << std::endl;
		else if (j.GetOperation() == 8)
			std::cout << "WRT" << std::endl;
		
	}
	REQUIRE((result.first == output));

}
