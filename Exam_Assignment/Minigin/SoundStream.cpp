#include "MiniginPCH.h"
#include "SoundStream.h"
#include <iostream>

dae::SoundStream::SoundStream( std::string path )
	:m_pMixMusic{ Mix_LoadMUS( path.c_str( )) }
{
	if ( m_pMixMusic == nullptr )
	{
		std::cout << "Exception occurred!\n";
		std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
		try
		{
			throw IsLoaded();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}
	}
}

dae::SoundStream::~SoundStream( )
{
	Mix_FreeMusic( m_pMixMusic );
	m_pMixMusic = nullptr;
}

bool dae::SoundStream::IsLoaded( ) const
{
	return m_pMixMusic != nullptr;
}

bool dae::SoundStream::Play(bool repeat ) const
{
	if ( m_pMixMusic != nullptr )
	{
		int result{ Mix_PlayMusic( m_pMixMusic, repeat ? -1 : 1 ) };
		return result == 0 ? true : false;
	}
	else
	{
		return false;
	}
}

void dae::SoundStream::Stop( )
{
	Mix_HaltMusic( );
}
void dae::SoundStream::Pause( )
{
	Mix_PauseMusic( );
}

void dae::SoundStream::Resume( )
{
	Mix_ResumeMusic( );
}

int dae::SoundStream::GetVolume( )
{
	return Mix_VolumeMusic( -1 );
}

bool dae::SoundStream::IsPlaying( )
{
	return Mix_PlayingMusic( ) == 0 ? false : true;
}

void dae::SoundStream::SetVolume( int value )
{
	Mix_VolumeMusic( value );
}

