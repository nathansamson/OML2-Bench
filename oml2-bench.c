#include <stdio.h>
#include <unistd.h>

#include <oml2/omlc.h>

void print_help() {
    printf("Usage: \n");
    printf("oml2-bench /delay/ /count/\n");
    
    printf("  count: The number of messages to print (or send to OML).\n");
    printf("  delay: Time in ms between two messages. If 0 it will sent it as fast as possible.\n");
}

int main(int argc, const char** argv) {
	int result = omlc_init("OML2Bench", &argc, argv, 0);
	
	if (argc < 3) {
	    print_help();
	    return 1;
	}
	
	uint64_t max_count = atoi(argv[2]);
	uint64_t current_count = 0;
	useconds_t delay = 1.0 / atoi(argv[1]) * 1000 * 1000;
	if (result == -1) {
		fprintf(stderr, "Could not initialize OML\n");
		exit(1);	
	}

	OmlMPDef mp_def[] = {
		{ "text", OML_STRING_VALUE },
		{ "counter", OML_UINT64_VALUE },
		{ 0, (OmlValueT)0 },
	};
	OmlMP *mp = omlc_add_mp("log_info", mp_def);

	if (omlc_start() == -1) {
		fprintf(stderr, "Error starting up OML streams\n");
		exit(1);
	}

	OmlValueU values[2];

	for (current_count = 1; current_count <= max_count; current_count++) {
		char text[512];
		
		sprintf(text, "This is some string that I will be logging " \
                       "as fast as I can. This is the %u that I sent.\n", 
                current_count);
		printf(text);
		omlc_set_string(values[0], text);
		omlc_set_uint64(values[1], current_count);
		omlc_inject(mp, values);
		if (delay != 0) usleep(delay);
	}

	omlc_close();

	return 0;
}
