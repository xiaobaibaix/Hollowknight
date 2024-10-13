#pragma once
#include <vector>
#include <graphics.h>

class Atlas {
public:

	Atlas() = default;
	~Atlas() = default;

	void load(LPCTSTR path_template,int num);

	void clear();

	int get_size()const;

	IMAGE* get_image(int idx);

	void add_image(const IMAGE& img);
private:
	std::vector<IMAGE> img_list;
};