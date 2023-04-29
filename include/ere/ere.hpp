#ifndef __ERE_HPP__
#define __ERE_HPP__

#include "api/camera_api.hpp"
#include "api/render_api.hpp"
#include "api/shader_api.hpp"
#include "api/window_api.hpp"
#include "api/cubemap_api.hpp"
#include "api/texture_api.hpp"
#include "api/texture2d_api.hpp"
#include "api/framebuffer_api.hpp"
#include "api/index_buffer_api.hpp"
#include "api/vertex_array_api.hpp"
#include "api/vertex_buffer_api.hpp"

#include "core/core.hpp"
#include "core/layer.hpp"
#include "core/i_layer.hpp"
#include "core/logger.hpp"
#include "core/camera_3d.hpp"
#include "core/application.hpp"
#include "core/entry_point.hpp"
#include "core/platform_detect.hpp"

#include "events/events.hpp"
#include "events/key_events.hpp"
#include "events/mouse_events.hpp"
#include "events/window_events.hpp"
#include "events/app_events.hpp"

#include "mappings/key_map.hpp"
#include "mappings/mouse_map.hpp"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#endif
