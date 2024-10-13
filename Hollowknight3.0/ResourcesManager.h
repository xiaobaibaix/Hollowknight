#pragma once
#include "ManagerSingle.h"
#include "Atlas.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <graphics.h>

class ResourcesManager :public ManagerSingle<ResourcesManager> {
	friend class ManagerSingle<ResourcesManager>;
public:

	struct ImageResInfo {
		std::string id;
		LPCTSTR path;
	};

	struct AtlasResInfo {
		std::string id;
		LPCTSTR path;
		int num_frame = 0;
	};

	void load();

	Atlas* find_atlas(const std::string& id) const;

	IMAGE* find_image(const std::string& id) const;
	
private:
	ResourcesManager() = default;
	~ResourcesManager() = default;
	//
	//·­×ª
	//
	void flip_image(IMAGE* src_img, IMAGE* dst_img, int num_h = 1);

	void flip_image(const std::string& src_id, const std::string dst_id, int num_h = 1);

	void flip_atlas(const std::string& src_id, const std::string dst_id);
	//--

	static inline bool check_image_valid(IMAGE* img);
private:

	std::unordered_map<std::string, Atlas*> atlas_pool;
	std::unordered_map<std::string, IMAGE*> image_pool;

	static const std::vector<ImageResInfo> image_info_list;
	static const std::vector<AtlasResInfo> atlas_info_list;

};


