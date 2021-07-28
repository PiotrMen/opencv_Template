#include "image_filters.h"

void image_filters::operator()(int thread_index)
{

	while (true)
	{
		std::cout << thread_index << std::endl;

		//exit program variable
		if (data_box.global_exit)
			break;

	}
}