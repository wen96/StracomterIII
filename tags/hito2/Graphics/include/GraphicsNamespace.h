/*
 * GraphicsNamespace.h
 *
 *  Created on: Feb 10, 2012
 *      Author: Chutaos Team
 */

#ifndef GRAPHICSNAMESPACE_H_
#define GRAPHICSNAMESPACE_H_

namespace Graphics{
	namespace Texturas{
		enum Type{
			t_wall = 0,
			t_floor = 1,
			t_wallFloor = 2,
			t_size = 3
		};
	}

	namespace Projection{
		enum Type {
			c_none = 0,
			c_ortho = 1,
			c_perspective = 2
		};
	}

	namespace MatrixMode{
		enum Type {
			m_none = 0,
			m_modelview = 1,
			m_projection = 2,
			m_texture = 3
		};
	}

	namespace ModeRender{
			enum Mode {
				m_point = 0,
				m_line = 1,
				m_polygon = 2,
			};
		}
	namespace DirectNodes {
		enum Index
			{
				c_escena = 0,      	//!< Cármara del escenario
				c_mapa = 1,      	//!< Cámara del mini mapa
				c_hud = 2,     		//!< Cámara del HUD
				t_escena = 3,     	//!< Transformación de la escena
				t_hud = 4,      	//!< Transformación del HUD
				t_console = 5, 		//!< Transformación de la consola
				t_menu = 6, 		//!< Transformación del menu (pausa, game over, win..)
				t_puntuacion = 7,	//!< Texto de la puntuación.
				t_hp = 8,			//!< Texto HP.
				t_ray = 9,			//!< Transformación de los Rayos.
				t_light0 = 10,		//!< Luz 0.
				t_light1 = 11,		//!< Luz 1.
				t_light2 = 12,		//!< Luz 2.
				t_mapa = 13,		//!< Transformación de los mapas.
				t_enemigos = 14,	//!< Texto enemigos.
				t_balas = 15,		//!< Texto balas.
				t_screen = 16,
				t_fps = 17,         //Para mostrar fps
				t_time = 18,		// Tiempo de la partida


				size = 19
			};
		}
	namespace DirectNodesMenu {
		enum Index
			{
				c_menu = 0,      	//!< Cármara del escenario
				t_menu = 1,


				size = 2
			};
		}
	namespace StracomerTrees {
		enum Type
			{
				gameAction = 0,      	//!< Cármara del escenario
				gameMenu = 1,


				size = 2
			};
		}
	namespace Menus {
		enum Index
			{
				m_none = 0,			//!< No se muestra ningun menu
				m_inicio = 1,
				m_loading = 2,     	//!< Menu de loading
				m_pause = 3,      	//!< Menu de pause
				m_gameover = 4,     //!< Menu de game over
				m_closing = 5,
				m_win = 6,

				size = 7
			};
		}
	namespace Font{
		enum Name{
			Monospace,
			Serif,
			SansSerif,
			BebasNeue,
			Coolvetica,
			Absender,

			size
		};
	}
}


#endif /* GRAPHICSNAMESPACE_H_ */
