LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := kawaiijellyfish_shared

LOCAL_MODULE_FILENAME := libkawaiijellyfish

LOCAL_CPPFLAGS += -fexceptions

LOCAL_SRC_FILES := ./main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameManager/SceneManager.cpp \
                   ../../Classes/GameManager/UIManager.cpp \
                   ../../Classes/GameScene/BasicScene.cpp \
                   ../../Classes/GameScene/HelloWorldScene.cpp \
                   ../../Classes/GameScene/MainScene.cpp \
                   ../../Classes/GameScene/ReadXMLInCScene.cpp \
                   ../../Classes/GameScene/ReadJsonScene.cpp \
                   ../../Classes/GameScene/SqliteFileScene.cpp \
                   ../../Classes/GameUtils/JNIProxy.cpp \
                   ../../Classes/GameUtils/XMLUtils.cpp \
                   ../../Classes/GameUtils/JsonUtils.cpp \
                   ../../libs/libJson/_internal/Source/internalJSONNode.cpp \
                   ../../libs/libJson/_internal/Source/libjson.cpp \
                   ../../libs/libJson/_internal/Source/JSONWriter.cpp \
                   ../../libs/libJson/_internal/Source/JSONWorker.cpp \
                   ../../libs/libJson/_internal/Source/JSONValidator.cpp \
                   ../../libs/libJson/_internal/Source/JSONStream.cpp \
                   ../../libs/libJson/_internal/Source/JSONPreparse.cpp \
                   ../../libs/libJson/_internal/Source/JSONNode_Mutex.cpp \
                   ../../libs/libJson/_internal/Source/JSONNode.cpp \
                   ../../libs/libJson/_internal/Source/JSONMemory.cpp \
                   ../../libs/libJson/_internal/Source/JSONIterators.cpp \
                   ../../libs/libJson/_internal/Source/JSONDebug.cpp \
                   ../../libs/libJson/_internal/Source/JSONChildren.cpp \
                   ../../libs/libJson/_internal/Source/JSONAllocator.cpp \
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/GameManager \
					$(LOCAL_PATH)/../../Classes/GameScene \
					$(LOCAL_PATH)/../../Classes/GameUtils \
					$(LOCAL_PATH)/../../libs/libJson \
					$(LOCAL_PATH)/../../libs/libJson/_internal/Source \
                    $(LOCAL_PATH)/../../libs/libJson/_internal/Source/JSONDefs \
                    $(LOCAL_PATH)/../../libs/libJson/_internal/Dependencies/libbase64++ \
                    $(LOCAL_PATH)/../../libs/libJson/_internal/Dependencies/mempool++

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
