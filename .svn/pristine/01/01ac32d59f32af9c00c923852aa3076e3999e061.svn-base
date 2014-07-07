#ifndef __TIME__HPP__
#define __TIME__HPP__


#if defined(_MSC_VER)
#  define NOMINMAX // workaround un bug dans windows.h qui define des macros
                   // "min" et "max" qui entrent en conflit avec la STL.
#  include <windows.h>
#else
#  include <sys/time.h>
#endif

namespace Utils
{

   /**
    * Implémente un chronométre qui mesure le temps etre deux appels.
    */
   class CTimer
   {
   private:
#     if defined(_MSC_VER)
         LARGE_INTEGER m_depart;
#     else
         timeval m_depart;
#     endif

   public:
      /**
       * Démarre le timer.
       * 
       * Cette fonction sert à démarrer le timer. Si le timer est  déja
       * démarrer, elle le redémarre simplement.
       */
      inline void start()
      {
#        if defined(_MSC_VER)
            QueryPerformanceCounter(&m_depart);
#        else
            gettimeofday(&m_depart, 0);
#        endif

      };

      /**
       * Retourne le nombre de secondes depuis le départ du timer.
       * 
       * @return Nombre de secondes écoulés depuis le départ du timer
       */
      inline float GetSecondes() const
      {
#        if defined(_MSC_VER)
            LARGE_INTEGER now;
            LARGE_INTEGER freq;

            QueryPerformanceCounter(&now);
            QueryPerformanceFrequency(&freq);

            return (now.QuadPart - m_depart.QuadPart) / static_cast<float>(freq.QuadPart);
#        else
            timeval now;
            gettimeofday(&now, 0);

            return now.tv_sec - m_depart.tv_sec + (now.tv_usec - m_depart.tv_usec) / 1000000.0f;
#        endif
      };
   };
}

#endif
