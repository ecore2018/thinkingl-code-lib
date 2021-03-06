#include "stdafx.h"
#include "error.h"
#include <evcode.h>

#include <vfwmsgs.h>

CError s_error;

CError::CError()
{
	InitVFWErrorMsg();
	InitEVMsg();
}


CError::~CError()
{
}

void CError::InitVFWErrorMsg()
{
#define DEF_ERROR(x) m_hresultErrorMsgTable[x] = L#x

	DEF_ERROR(VFW_E_INVALIDMEDIATYPE);
	DEF_ERROR(VFW_E_INVALIDSUBTYPE);
	DEF_ERROR(VFW_E_NEED_OWNER);
	DEF_ERROR(VFW_E_ENUM_OUT_OF_SYNC);
	DEF_ERROR(VFW_E_ALREADY_CONNECTED);
	DEF_ERROR(VFW_E_FILTER_ACTIVE);
	DEF_ERROR(VFW_E_NO_TYPES);
	DEF_ERROR(VFW_E_NO_ACCEPTABLE_TYPES);
	DEF_ERROR(VFW_E_INVALID_DIRECTION);
	DEF_ERROR(VFW_E_NOT_CONNECTED);
	DEF_ERROR(VFW_E_NO_ALLOCATOR);
	DEF_ERROR(VFW_E_RUNTIME_ERROR);
	DEF_ERROR(VFW_E_BUFFER_NOTSET);
	DEF_ERROR(VFW_E_BUFFER_OVERFLOW);
	DEF_ERROR(VFW_E_BADALIGN);
	DEF_ERROR(VFW_E_ALREADY_COMMITTED);
	DEF_ERROR(VFW_E_BUFFERS_OUTSTANDING);
	DEF_ERROR(VFW_E_NOT_COMMITTED);
	DEF_ERROR(VFW_E_SIZENOTSET);
	DEF_ERROR(VFW_E_NO_CLOCK);
	DEF_ERROR(VFW_E_NO_SINK);
	DEF_ERROR(VFW_E_NO_INTERFACE);
	DEF_ERROR(VFW_E_NOT_FOUND);
	DEF_ERROR(VFW_E_CANNOT_CONNECT);
	DEF_ERROR(VFW_E_CANNOT_RENDER);
	DEF_ERROR(VFW_E_CHANGING_FORMAT);
	DEF_ERROR(VFW_E_NO_COLOR_KEY_SET);
	DEF_ERROR(VFW_E_NOT_OVERLAY_CONNECTION);
	DEF_ERROR(VFW_E_NOT_SAMPLE_CONNECTION);
	DEF_ERROR(VFW_E_PALETTE_SET);
	DEF_ERROR(VFW_E_COLOR_KEY_SET);
	DEF_ERROR(VFW_E_NO_COLOR_KEY_FOUND);
	DEF_ERROR(VFW_E_NO_PALETTE_AVAILABLE);
	DEF_ERROR(VFW_E_NO_DISPLAY_PALETTE);
	DEF_ERROR(VFW_E_TOO_MANY_COLORS);
	DEF_ERROR(VFW_E_STATE_CHANGED);
	DEF_ERROR(VFW_E_NOT_STOPPED);
	DEF_ERROR(VFW_E_NOT_PAUSED);
	DEF_ERROR(VFW_E_NOT_RUNNING);
	DEF_ERROR(VFW_E_WRONG_STATE);
	DEF_ERROR(VFW_E_START_TIME_AFTER_END);
	DEF_ERROR(VFW_E_INVALID_RECT);
	DEF_ERROR(VFW_E_TYPE_NOT_ACCEPTED);
	DEF_ERROR(VFW_E_SAMPLE_REJECTED);
	DEF_ERROR(VFW_E_SAMPLE_REJECTED_EOS);
	DEF_ERROR(VFW_E_DUPLICATE_NAME);
	DEF_ERROR(VFW_S_DUPLICATE_NAME);
	DEF_ERROR(VFW_E_TIMEOUT);
	DEF_ERROR(VFW_E_INVALID_FILE_FORMAT);
	DEF_ERROR(VFW_E_ENUM_OUT_OF_RANGE);
	DEF_ERROR(VFW_E_CIRCULAR_GRAPH);
	DEF_ERROR(VFW_E_NOT_ALLOWED_TO_SAVE);
	DEF_ERROR(VFW_E_TIME_ALREADY_PASSED);
	DEF_ERROR(VFW_E_ALREADY_CANCELLED);
	DEF_ERROR(VFW_E_CORRUPT_GRAPH_FILE);
	DEF_ERROR(VFW_E_ADVISE_ALREADY_SET);
	DEF_ERROR(VFW_S_STATE_INTERMEDIATE);
	DEF_ERROR(VFW_E_NO_MODEX_AVAILABLE);
	DEF_ERROR(VFW_E_NO_ADVISE_SET);
	DEF_ERROR(VFW_E_NO_FULLSCREEN);
	DEF_ERROR(VFW_E_IN_FULLSCREEN_MODE);
	DEF_ERROR(VFW_E_UNKNOWN_FILE_TYPE);
	DEF_ERROR(VFW_E_CANNOT_LOAD_SOURCE_FILTER);
	DEF_ERROR(VFW_S_PARTIAL_RENDER);
	DEF_ERROR(VFW_E_FILE_TOO_SHORT);
	DEF_ERROR(VFW_E_INVALID_FILE_VERSION);
	DEF_ERROR(VFW_S_SOME_DATA_IGNORED);
	DEF_ERROR(VFW_S_CONNECTIONS_DEFERRED);
	DEF_ERROR(VFW_E_INVALID_CLSID);
	DEF_ERROR(VFW_E_INVALID_MEDIA_TYPE);
	DEF_ERROR(VFW_E_BAD_KEY);
	DEF_ERROR(VFW_S_NO_MORE_ITEMS);
	DEF_ERROR(VFW_E_SAMPLE_TIME_NOT_SET);
	DEF_ERROR(VFW_S_RESOURCE_NOT_NEEDED);
	DEF_ERROR(VFW_E_MEDIA_TIME_NOT_SET);
	DEF_ERROR(VFW_E_NO_TIME_FORMAT_SET);
	DEF_ERROR(VFW_E_MONO_AUDIO_HW);
	DEF_ERROR(VFW_S_MEDIA_TYPE_IGNORED);
	DEF_ERROR(VFW_E_NO_DECOMPRESSOR);
	DEF_ERROR(VFW_E_NO_AUDIO_HARDWARE);
	DEF_ERROR(VFW_S_VIDEO_NOT_RENDERED);
	DEF_ERROR(VFW_S_AUDIO_NOT_RENDERED);
	DEF_ERROR(VFW_E_RPZA);
	DEF_ERROR(VFW_S_RPZA);
	DEF_ERROR(VFW_E_PROCESSOR_NOT_SUITABLE);
	DEF_ERROR(VFW_E_UNSUPPORTED_AUDIO);
	DEF_ERROR(VFW_E_UNSUPPORTED_VIDEO);
	DEF_ERROR(VFW_E_MPEG_NOT_CONSTRAINED);
	DEF_ERROR(VFW_E_NOT_IN_GRAPH);
	DEF_ERROR(VFW_S_ESTIMATED);
	DEF_ERROR(VFW_E_NO_TIME_FORMAT);
	DEF_ERROR(VFW_E_READ_ONLY);
	DEF_ERROR(VFW_S_RESERVED);
	DEF_ERROR(VFW_E_BUFFER_UNDERFLOW);
	DEF_ERROR(VFW_E_UNSUPPORTED_STREAM);
	DEF_ERROR(VFW_E_NO_TRANSPORT);
	DEF_ERROR(VFW_S_STREAM_OFF);
	DEF_ERROR(VFW_S_CANT_CUE);
	DEF_ERROR(VFW_E_BAD_VIDEOCD);
	DEF_ERROR(VFW_S_NO_STOP_TIME);
	DEF_ERROR(VFW_E_OUT_OF_VIDEO_MEMORY);
	DEF_ERROR(VFW_E_VP_NEGOTIATION_FAILED);
	DEF_ERROR(VFW_E_DDRAW_CAPS_NOT_SUITABLE);
	DEF_ERROR(VFW_E_NO_VP_HARDWARE);
	DEF_ERROR(VFW_E_NO_CAPTURE_HARDWARE);
	DEF_ERROR(VFW_E_DVD_OPERATION_INHIBITED);
	DEF_ERROR(VFW_E_DVD_INVALIDDOMAIN);
	DEF_ERROR(VFW_E_DVD_NO_BUTTON);
	DEF_ERROR(VFW_E_DVD_GRAPHNOTREADY);
	DEF_ERROR(VFW_E_DVD_RENDERFAIL);
	DEF_ERROR(VFW_E_DVD_DECNOTENOUGH);
	DEF_ERROR(VFW_E_DDRAW_VERSION_NOT_SUITABLE);
	DEF_ERROR(VFW_E_COPYPROT_FAILED);
	DEF_ERROR(VFW_S_NOPREVIEWPIN);
	DEF_ERROR(VFW_E_TIME_EXPIRED);
	DEF_ERROR(VFW_S_DVD_NON_ONE_SEQUENTIAL);
	DEF_ERROR(VFW_E_DVD_WRONG_SPEED);
	DEF_ERROR(VFW_E_DVD_MENU_DOES_NOT_EXIST);
	DEF_ERROR(VFW_E_DVD_CMD_CANCELLED);
	DEF_ERROR(VFW_E_DVD_STATE_WRONG_VERSION);
	DEF_ERROR(VFW_E_DVD_STATE_CORRUPT);
	DEF_ERROR(VFW_E_DVD_STATE_WRONG_DISC);
	DEF_ERROR(VFW_E_DVD_INCOMPATIBLE_REGION);
	DEF_ERROR(VFW_E_DVD_NO_ATTRIBUTES);
	DEF_ERROR(VFW_E_DVD_NO_GOUP_PGC);
	DEF_ERROR(VFW_E_DVD_LOW_PARENTAL_LEVEL);
	DEF_ERROR(VFW_E_DVD_NOT_IN_KARAOKE_MODE);
	DEF_ERROR(VFW_S_DVD_CHANNEL_CONTENTS_NOT_AVAILABLE);
	DEF_ERROR(VFW_S_DVD_NOT_ACCURATE);
	DEF_ERROR(VFW_E_FRAME_STEP_UNSUPPORTED);
	DEF_ERROR(VFW_E_DVD_STREAM_DISABLED);
	DEF_ERROR(VFW_E_DVD_TITLE_UNKNOWN);
	DEF_ERROR(VFW_E_DVD_INVALID_DISC);
	DEF_ERROR(VFW_E_DVD_NO_RESUME_INFORMATION);
	DEF_ERROR(VFW_E_PIN_ALREADY_BLOCKED_ON_THIS_THREAD);
	DEF_ERROR(VFW_E_PIN_ALREADY_BLOCKED);
	DEF_ERROR(VFW_E_CERTIFICATION_FAILURE);
	DEF_ERROR(VFW_E_VMR_NOT_IN_MIXER_MODE);
	DEF_ERROR(VFW_E_VMR_NO_AP_SUPPLIED);
	DEF_ERROR(VFW_E_VMR_NO_DEINTERLACE_HW);
	DEF_ERROR(VFW_E_VMR_NO_PROCAMP_HW);
	DEF_ERROR(VFW_E_DVD_VMR9_INCOMPATIBLEDEC);
	DEF_ERROR(VFW_E_VMR_NO_AP_SUPPLIED);
	DEF_ERROR(VFW_E_VMR_NO_DEINTERLACE_HW);
	DEF_ERROR(VFW_E_VMR_NO_PROCAMP_HW);
	DEF_ERROR(VFW_E_DVD_VMR9_INCOMPATIBLEDEC);
	DEF_ERROR(VFW_E_NO_COPP_HW);
	DEF_ERROR(VFW_E_DVD_NONBLOCKING);
	DEF_ERROR(VFW_E_DVD_TOO_MANY_RENDERERS_IN_FILTER_GRAPH);
	DEF_ERROR(VFW_E_DVD_NON_EVR_RENDERER_IN_FILTER_GRAPH);
	DEF_ERROR(VFW_E_DVD_RESOLUTION_ERROR);
	DEF_ERROR(E_PROP_SET_UNSUPPORTED);
	DEF_ERROR(E_PROP_ID_UNSUPPORTED);
	DEF_ERROR(VFW_E_CODECAPI_LINEAR_RANGE);
	DEF_ERROR(VFW_E_CODECAPI_ENUMERATED);
	DEF_ERROR(VFW_E_CODECAPI_NO_DEFAULT);
	DEF_ERROR(VFW_E_CODECAPI_NO_CURRENT_VALUE);
	DEF_ERROR(VFW_E_DVD_CHAPTER_DOES_NOT_EXIST);
}

std::wstring CError::GetErrorMsg(HRESULT hr)
{
	CHResultErrorMsgMap::const_iterator cIt = m_hresultErrorMsgTable.find(hr);
	if (cIt != m_hresultErrorMsgTable.end())
	{
		return cIt->second;
	}
	else
	{
		return L"Can't find the error code!";
	}
}


std::wstring CError::GetEVMsg(long evCode)
{
	CHResultErrorMsgMap::const_iterator cIt = m_evMsgTable.find(evCode);
	if (cIt != m_evMsgTable.end())
	{
		return cIt->second;
	}
	else
	{
		return L"Can't find the Event code!";
	}
}

std::wstring CError::ErrorMsg(HRESULT hr)
{
	return s_error.GetErrorMsg(hr);
}

void CError::InitEVMsg()
{
#define DEF_EV_MSG(x) m_evMsgTable[x] = L#x

	DEF_EV_MSG(EC_SYSTEMBASE);
	DEF_EV_MSG(EC_USER);
	DEF_EV_MSG(EC_COMPLETE);
	DEF_EV_MSG(EC_USERABORT);
	DEF_EV_MSG(EC_ERRORABORT);
	DEF_EV_MSG(EC_TIME);
	DEF_EV_MSG(EC_REPAINT);
	DEF_EV_MSG(EC_STREAM_ERROR_STOPPED);
	DEF_EV_MSG(EC_STREAM_ERROR_STILLPLAYING);
	DEF_EV_MSG(EC_ERROR_STILLPLAYING);
	DEF_EV_MSG(EC_PALETTE_CHANGED);
	DEF_EV_MSG(EC_VIDEO_SIZE_CHANGED);
	DEF_EV_MSG(EC_QUALITY_CHANGE);
	DEF_EV_MSG(EC_SHUTTING_DOWN);
	DEF_EV_MSG(EC_CLOCK_CHANGED);
	DEF_EV_MSG(EC_PAUSED);
	DEF_EV_MSG(EC_OPENING_FILE);
	DEF_EV_MSG(EC_BUFFERING_DATA);
	DEF_EV_MSG(EC_FULLSCREEN_LOST);
	DEF_EV_MSG(EC_ACTIVATE);
	DEF_EV_MSG(EC_NEED_RESTART);
	DEF_EV_MSG(EC_WINDOW_DESTROYED);
	DEF_EV_MSG(EC_DISPLAY_CHANGED);
	DEF_EV_MSG(EC_STARVATION);
	DEF_EV_MSG(EC_OLE_EVENT);
	DEF_EV_MSG(EC_NOTIFY_WINDOW);
	DEF_EV_MSG(EC_STREAM_CONTROL_STOPPED);
	DEF_EV_MSG(EC_STREAM_CONTROL_STARTED);
	DEF_EV_MSG(EC_END_OF_SEGMENT);
	DEF_EV_MSG(EC_SEGMENT_STARTED);
	DEF_EV_MSG(EC_LENGTH_CHANGED);
	DEF_EV_MSG(EC_DEVICE_LOST);
	DEF_EV_MSG(EC_SAMPLE_NEEDED);
	DEF_EV_MSG(EC_PROCESSING_LATENCY);
	DEF_EV_MSG(EC_SAMPLE_LATENCY);
	DEF_EV_MSG(EC_SCRUB_TIME);
	DEF_EV_MSG(EC_STEP_COMPLETE);
	DEF_EV_MSG(EC_TIMECODE_AVAILABLE);
	DEF_EV_MSG(EC_EXTDEVICE_MODE_CHANGE);
	DEF_EV_MSG(EC_STATE_CHANGE);
	DEF_EV_MSG(EC_GRAPH_CHANGED);
	DEF_EV_MSG(EC_CLOCK_UNSET);
	DEF_EV_MSG(EC_VMR_RENDERDEVICE_SET);
	DEF_EV_MSG(EC_VMR_SURFACE_FLIPPED);
	DEF_EV_MSG(EC_VMR_RECONNECTION_FAILED);
	DEF_EV_MSG(EC_PREPROCESS_COMPLETE);
	DEF_EV_MSG(EC_CODECAPI_EVENT);
	DEF_EV_MSG(EC_WMT_EVENT_BASE);
	DEF_EV_MSG(EC_WMT_INDEX_EVENT);
	DEF_EV_MSG(EC_WMT_EVENT);
	DEF_EV_MSG(EC_BUILT);
	DEF_EV_MSG(EC_UNBUILT);
	DEF_EV_MSG(EC_SKIP_FRAMES);
	DEF_EV_MSG(EC_PLEASE_REOPEN);
	DEF_EV_MSG(EC_STATUS);
	DEF_EV_MSG(EC_MARKER_HIT);
	DEF_EV_MSG(EC_LOADSTATUS);
	DEF_EV_MSG(EC_FILE_CLOSED);
	DEF_EV_MSG(EC_ERRORABORTEX);
	DEF_EV_MSG(EC_NEW_PIN);
	DEF_EV_MSG(EC_EOS_SOON);
	DEF_EV_MSG(EC_CONTENTPROPERTY_CHANGED);
	DEF_EV_MSG(EC_BANDWIDTHCHANGE);
	DEF_EV_MSG(EC_VIDEOFRAMEREADY);
}

std::wstring CError::EVMsg(long evCode)
{
	return s_error.GetEVMsg(evCode);
}
