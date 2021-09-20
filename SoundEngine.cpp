#include "stdafx.h"
#include "SoundEngine.h"

// private: Functions:

void sfx::SoundEngine::initVariables()
{
// SFX:

	this->sfxVolume = 0.5f;

// Music:

	this->musicVolume = 0.5f;
	this->fadeStep = 0.007f;
	this->fadeRate = 1.f;
}

void sfx::SoundEngine::initSoundSystem()
{
	// System initialization
	FMOD::System_Create(&this->soundSystem);
	this->soundSystem->init(static_cast<int>(sfx::ChannelsMax * 2u), FMOD_DEFAULT, 0);

	// Creating channel groups
	this->soundSystem->createChannelGroup("SFX", &this->sfxGroup);
	this->soundSystem->createChannelGroup("Music", &this->musicGroup);
	this->soundSystem->getMasterChannelGroup(&this->masterGroup);

	//Set the sfxGruop and musicGroup to be children of the master group
	this->masterGroup->addGroup(this->sfxGroup);
	this->masterGroup->addGroup(this->musicGroup);

	// Attaching channels to SFX group
	for (unsigned int i = 0; i < sfx::ChannelsMax; i++)
	{
		this->soundChannels[i]->setChannelGroup(this->sfxGroup);
	}

	// Attaching channels to Music group
	for (unsigned int i = 0; i < sfx::ChannelsMax; i++)
	{
		this->musicChannels[i]->setChannelGroup(this->musicGroup);
	}

	// Setting SFX volume
	this->sfxGroup->setVolume(this->sfxVolume);

	// Setting Music volume
	this->musicGroup->setVolume(this->musicVolume);
}


// Constructors and Destructor:

sfx::SoundEngine::SoundEngine()
{
	this->initVariables();

	// Sound system initialization
	this->initSoundSystem();
}

sfx::SoundEngine::~SoundEngine()
{
	// FMOD deleting it's pointers automatically?
	// Trying to delete FMOD pointers couses an error: "0x...: Access violation reading location 0x...".
	// Seems like pointers was already deleted by FMOD.

	// Stopping all channels
	this->masterGroup->stop();

	//Releasing sound resources
	for (unsigned int i = 0; i < sfx::ChannelsMax; i++)
	{
		this->sounds[i]->release();
		this->music[i]->release();
	}

	// Releasing sound system resources
	this->soundSystem->close();
	this->soundSystem->release();
}


// Accessors:

const float& sfx::SoundEngine::getSfxVolume() const
{
	return this->sfxVolume;
}

const float& sfx::SoundEngine::getMusicVolume() const
{
	return this->musicVolume;
}

const float& sfx::SoundEngine::getFadeRate() const
{
	return this->fadeRate;
}

const bool sfx::SoundEngine::isPlaying(sfx::Music name) const
{
	bool playing;

	this->musicChannels[static_cast<unsigned int>(name)]->isPlaying(&playing);

	return playing;
}

const bool sfx::SoundEngine::isMusicPlaying() const
{
	bool playing;

	this->musicGroup->isPlaying(&playing);

	return playing;
}

const bool sfx::SoundEngine::isPaused(sfx::Music name) const
{
	bool paused;

	this->musicChannels[static_cast<unsigned int>(name)]->getPaused(&paused);

	return paused;
}

const bool sfx::SoundEngine::isMusicPaused() const
{
	bool paused;

	this->musicGroup->getPaused(&paused);

	return paused;
}


// Modifiers:

void sfx::SoundEngine::increaseSfxVolume(const float& value)
{
	this->sfxVolume += value;

	if (this->sfxVolume > 1.f)
	{
		this->sfxVolume = 1.f;
	}
	else if (this->sfxVolume < 0.f)
	{
		this->sfxVolume = 0.f;
	}

	this->updateSfxVolume();
}

void sfx::SoundEngine::increaseMusicVolume(const float& value)
{
	this->musicVolume += value;

	if (this->musicVolume > 1.f)
	{
		this->musicVolume = 1.f;
	}
	else if (this->musicVolume < 0.f)
	{
		this->musicVolume = 0.f;
	}

	this->updateMusicVolume();
}

void sfx::SoundEngine::fade(const float& fade_step)
{
	this->fadeRate += fadeStep;

	if (this->fadeRate > 1.f)
	{
		this->fadeRate = 1.f;
	}
	else if (this->fadeRate < 0.f)
	{
		this->fadeRate = 0.f;
	}

	this->updateMusicVolume();
}


// Functions:

void sfx::SoundEngine::initSound(const sfx::Sound name, const char* file_path)
{
	this->soundSystem->createSound(file_path, FMOD_DEFAULT, 0, &this->sounds[static_cast<unsigned int>(name)]);
}

void sfx::SoundEngine::playSound(const sfx::Sound name)
{
	this->soundSystem->playSound(this->sounds[static_cast<unsigned int>(name)], this->sfxGroup, false, &this->soundChannels[static_cast<unsigned int>(name)]);
}

void sfx::SoundEngine::initMusic(const sfx::Music name, const char* file_path)
{
	this->musicFiles[name] = file_path;
}

void sfx::SoundEngine::playMusic(const sfx::Music name, const bool looped, const bool paused)
{
	if (looped == true)
	{
		this->soundSystem->createStream(this->musicFiles[name], FMOD_LOOP_NORMAL, 0, &this->music[static_cast<unsigned int>(name)]);
	}
	else
	{
		this->soundSystem->createStream(this->musicFiles[name], FMOD_DEFAULT, 0, &this->music[static_cast<unsigned int>(name)]);
	}

	this->soundSystem->playSound(this->music[static_cast<unsigned int>(name)], this->musicGroup, paused, &this->musicChannels[static_cast<unsigned int>(name)]);
}

void sfx::SoundEngine::pause(const sfx::Music name)
{
	this->musicChannels[static_cast<unsigned int>(name)]->setPaused(true);
}

void sfx::SoundEngine::unpause(const sfx::Music name)
{
	this->musicChannels[static_cast<unsigned int>(name)]->setPaused(false);
}

void sfx::SoundEngine::stop(const sfx::Music name)
{
	this->musicChannels[static_cast<unsigned int>(name)]->stop();
}

void sfx::SoundEngine::setPosition(const sfx::Music name, const unsigned int milliseconds)
{
	this->musicChannels[static_cast<unsigned int>(name)]->setPosition(milliseconds, FMOD_TIMEUNIT_MS);
}

void sfx::SoundEngine::fadeIn()
{
	if (this->getFadeRate() != 1)
	{
		this->fade(this->fadeStep);
	}

//	this->pause(index, false);
}

void sfx::SoundEngine::fadeOut()
{
	if (this->getFadeRate() != 0)
	{
		this->fade(-this->fadeStep);
	//	this->pause(index, false);
	}
	else
	{
	//	this->pause(index, true);
	}
}

void sfx::SoundEngine::updateSfxVolume()
{
	// SFX
	this->sfxGroup->setVolume(this->sfxVolume);
}

void sfx::SoundEngine::updateMusicVolume()
{
	// Music
	this->musicGroup->setVolume(this->musicVolume * this->fadeRate);
}

void sfx::SoundEngine::update(const float& dt)
{
	// System
	this->soundSystem->update();
}
