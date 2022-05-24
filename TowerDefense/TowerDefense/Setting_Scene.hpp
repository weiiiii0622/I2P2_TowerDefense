#ifndef SETTINGSCENE_HPP
#define SETTINGSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class SettingScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    int location; // 0: stage-select, 1: army-select
	explicit SettingScene() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int stage);
	void BGMSlideOnValueChanged(float value);
	void SFXSlideOnValueChanged(float value);
};

#endif // SETTINGSCENE_HPP


