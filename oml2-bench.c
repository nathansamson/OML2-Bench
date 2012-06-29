#include <stdio.h>

#include <oml2/omlc.h>

int main(int argc, const char** argv) {
	int result = omlc_init("OML2 Bench", &argc, argv, 0);
	int count = 10000;
	if (result == -1) {
		fprintf(stderr, "Could not initialize OML\n");
		exit(1);	
	}

	OmlMPDef mp_def[] = {
		{ "text", OML_STRING_VALUE },
		{ "counter", OML_INT_VALUE }
		{ 0, (OmlValueT)0 },
	};
	OmlMP* mp = omld_add_mp("log_info", mp_def);

	if (omlc_start() == -1) {
		fprintf(stderr; "Error starting up OML streams\n");
		exit(1);
	}

	OmlValueU values[2];

	for (int counter = 0; counter < count; count++) {
		char text[256];
		
		sprintf(text, "This is some string that I will be logging " \
                              "as fast as I can. This is the %i that I sent.", 
                        counter);

		oml_set_string(values[0], text);
		oml_set_counter(values[1], count);
	}

	omlc_close();

	return 0;
}
