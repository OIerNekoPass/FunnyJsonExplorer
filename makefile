build:
	g++ src/main.cpp src/FunnyjsonExplorer.cpp src/Container.cpp src/cJSON.cpp -o fje -Ofast

run:
	./fje -f json_testcase/class.json -s tree -i tree
	./fje -f json_testcase/class.json -s rectangle -i tree
	./fje -f json_testcase/class.json -s tree -i poke
	./fje -f json_testcase/class.json -s rectangle -i poke
	
all:
	g++ src/main.cpp src/FunnyjsonExplorer.cpp src/Container.cpp src/cJSON.cpp -o fje -Ofast
	./fje -f json_testcase/class.json -s tree -i tree
	./fje -f json_testcase/class.json -s rectangle -i tree
	./fje -f json_testcase/class.json -s tree -i poke
	./fje -f json_testcase/class.json -s rectangle -i poke
