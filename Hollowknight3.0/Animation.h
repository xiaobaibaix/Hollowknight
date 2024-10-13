#pragma once
#include "util.h"
#include "Timer.h"
#include "Vector2D.h"
#include "Atlas.h"

#include <vector>
#include <functional>

class Animation {
public:
	enum class AncherMode
	{
		Centerd,
		BottomCenterd
	};

public:
	Animation();
	~Animation();

	void reset();

	void set_ancher_mode(AncherMode mode);

	void set_position(const Vector2D& pos);
	
	void set_loop(bool flag);

	void set_interval(float val);

	void set_on_finished(std::function<void()> on_finished);

	void add_frame(IMAGE* img, int num_h);

	void add_frame(Atlas* atlas);

	void on_update(float delta);

	void on_render();
private:
	struct Frame {//֡

		Rect rect_src;
		IMAGE* img = nullptr;

		Frame() = default;
		Frame(IMAGE* img,const Rect& rect_src):img(img),rect_src(rect_src) {};
		~Frame() = default;
	};

private:
	Timer timer;
	Vector2D position;
	bool is_loop = true;
	size_t idx_frame = 0;
	std::vector<Frame> frame_list;
	std::function<void()> on_finished;
	AncherMode ancher_mode = AncherMode::Centerd;

};