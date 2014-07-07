
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include <iostream>


////////////////////////////////////////////////////////////
/// Play a given sound until it finishes
///
/// \param Sound : Sound to play
///
////////////////////////////////////////////////////////////
void PlaySound(sf::Sound& Sound)
{
    // Start the sound
    Sound.Play();

    // Loop while the sound is playing
    while (Sound.GetStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
        sf::Sleep(1000.1f);
    }
}


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Load the sound from a file
    sf::SoundBuffer Buffer;
    if (!Buffer.LoadFromFile("testFiles/sound/go.ogg"))
        return EXIT_SUCCESS;
    sf::Sound Sound(Buffer);

    // 1) Play the sound
    std::cout << "Play the sound - no spatialization" << std::endl;
    PlaySound(Sound);

    // 2) Use a lower global volume
    std::cout << "Play the sound - volume is 50%" << std::endl;
    sf::Listener::SetGlobalVolume(50.f);
    PlaySound(Sound);
    sf::Listener::SetGlobalVolume(100.f);

    // 3) Put the sound on the right of the listener (you will hear it in the right speaker)
    std::cout << "Play the sound - sound is on the right" << std::endl;
    Sound.SetPosition(1.f, 0.f, 0.f);
    PlaySound(Sound);
    Sound.SetPosition(0.f, 0.f, 0.f);

    // 4) Put the listener on the right of the sound (you will hear it in the left speaker)
    std::cout << "Play the sound - listener is on the right" << std::endl;
    sf::Listener::SetPosition(1.f, 0.f, 0.f);
    PlaySound(Sound);
    sf::Listener::SetPosition(0.f, 0.f, 0.f);

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
