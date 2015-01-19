LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					hellocpp/PayProxy.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
  					../../Classes/MenuLayer.cpp \
  					../../Classes/Chinese.cpp \
  					../../Classes/ComboEffect.cpp \
  					../../Classes/FloatWord.cpp \
  					../../Classes/GameData.cpp \
  					../../Classes/GameLayer.cpp \
  					../../Classes/LevelMsgLayer.cpp \
 	 				../../Classes/GameScene.cpp \
 	 				../../Classes/Star.cpp \
  					../../Classes/StarMatrix.cpp \
  					../../Classes/StarParticle.cpp \
  					../../Classes/TopMenu.cpp\
					../../Classes/Audio.cpp\
					../../Classes/MenuSceneHandler.cpp\
					../../Classes/MenuSceneHandlerReader.cpp\
					../../Classes/GameOver.cpp\
					../../Classes/GameOverReader.cpp\
					../../Classes/GameOverScene.cpp\
					../../Classes/GameOverLayer.cpp\
          			../../Classes/Upgrade.cpp\
          			../../Classes/UpgradeReader.cpp\
          			../../Classes/UpgradeLayer.cpp\
          			../../Classes/UpgradeScene.cpp\
					../../Classes/PlayerRank.cpp\
					../../Classes/Prize.cpp\
					../../Classes/PrizeReader.cpp\
          			../../Classes/PrizeScene.cpp\
          			../../Classes/PrizeLayer.cpp\
          			../../Classes/PrizeAnim.cpp\
					../../Classes/PrizeAnimReader.cpp\
          ../../Classes/CallAndroidMethod.cpp\
          ../../Classes/PowerStone.cpp\
          ../../Classes/PowerStoneReader.cpp\
          ../../Classes/PowerStoneLayer.cpp\
          ../../Classes/MenuScenePayHandler.cpp
          


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
              E:\cocosspace\StarGame\cocos2d\cocos\platform\android\jni

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
