#ifndef StracomterNamespace_H_
#define StracomterNamespace_H_

/** Namespace para variables globales y tipos en el core
 */
namespace Core {
	const float Radius = 30;
	namespace Element {
		enum Type {
				e_none = 0,
				e_camera = 1,
				e_light = 2,
				e_transform = 3,
				e_entity = 4,
				e_shape = 5,
				e_model = 6,
				e_texture = 7,
				e_text = 8,
				e_menu = 9,
				e_form = 10
		};
	}
	namespace Entities {
		enum Type
			{
				e_floor = 0,      //!< e_floor
				e_captain = 1,    //!< e_captain
				e_tecnic = 2,     //!< e_tecnic
				e_especialist = 3,//!< e_especialist
				e_explosive = 4,  //!< e_explosive
				e_enemy1 = 5,     //!< e_enemy1
				e_enemy2 = 6,     //!< e_enemy2
				e_enemy3 = 7,     //!< e_enemy3
				e_miniboss = 8,   //!< e_miniboss
				e_megaboss = 9,   //!< e_megaboss
				e_wall = 10,      //!< e_wall
				e_columne = 11,   //!< e_columne
				e_table = 12,     //!< e_table
				e_pointer = 13,     //!< e_table

				size = 14};       //!< size: Total de tipos, cambiar si aparecen mas

	}
	namespace SmartEntities {
		enum Type {
			e_captain,
			e_tecnic,
			e_especialist,
			e_explosives,
			e_enemy1,
			e_enemy2,
			e_enemy3,
			e_miniboss,
			e_megaboss,

			size
		};
	}
		//Para almacenar los datos de todos los personajes
	namespace Features{
		namespace e_captain {
			namespace Color{
				const float red = 0.4;
				const float green = 0.7;
				const float blue = 0.8;
			};
			const float HP = 100;
			const float DPS = 30;
			const float Speed = 150;
			const float Force = 3;
			const float Cadence = 100;
			const float Damage = 10;
			const unsigned int Moral = 3;
			const int expKill = 0;
		}
		namespace e_especialist {
			namespace Color{
				const float red = 0.9;
				const float green = 0.9;
				const float blue = 1.0;
			};
			const float HP = 125;
			const float DPS = 10;
			const float Speed = 130;
			const float Force = 3;
			const float Cadence = 200;
			const float Damage = 5;
			const unsigned int Moral = 2;
			const int expKill = 0;
			}
		namespace e_tecnic {
			namespace Color{
				const float red = 1.0;
				const float green = 0.9;
				const float blue = 0.9;
			};
			const float HP = 85;
			const float DPS = 3;
			const float Speed = 175;
			const float Force = 3;
			const float Cadence = 300;
			const float Damage = 7;
			const unsigned int Moral = 2;
			const int expKill = 0;
			}
		namespace e_explosive {
			namespace Color{
				const float red = 0.9;
				const float green = 1.0;
				const float blue = 0.9;
			};
			const float HP = 110;
			const float DPS = 0.75;
			const float Speed = 135;
			const float Force = 3;
			const float Cadence = 500;
			const float Damage = 60;
			const unsigned int Moral = 2;
			const int expKill = 0;
		}
		namespace e_enemy1 {
			namespace Color {
				const float red = 0.8;
				const float green = 0.3;
				const float blue = 0.0;
			};
			const float HP = 45;
			const float DPS = 10;
			const float Speed = 180;
			const float Force = 3;
			const float Cadence = 100;
			const float Damage = 1;
			const unsigned int Moral = 0;
			const int expKill = 3;
		}
		namespace e_enemy2 {
			namespace Color{
				const float red = 1.0;
				const float green = 0.0;
				const float blue = 0.0;
			};
			const float HP = 50;
			const float DPS = 15;
			const float Speed = 150;
			const float Force = 3;
			const float Cadence = 200;
			const float Damage = 3;
			const unsigned int Moral = 0;
			const int expKill = 5;
		}
		namespace e_enemy3 {
			namespace Color{
				const float red = 0.9;
				const float green = 0.6;
				const float blue = 0.2;
			};
			const float HP = 65;
			const float DPS = 20;
			const float Speed = 130;
			const float Force = 3;
			const float Cadence = 200;
			const float Damage = 4;
			const unsigned int Moral = 0;
			const int expKill = 7;
		}
	}
	namespace Key{
	 enum Code
	    {
	        A,            ///< The A key
	        B,            ///< The B key
	        C,            ///< The C key
	        D,            ///< The D key
	        E,            ///< The E key
	        F,            ///< The F key
	        G,            ///< The G key
	        H,            ///< The H key
	        I,            ///< The I key
	        J,            ///< The J key
	        K,            ///< The K key
	        L,            ///< The L key
	        M,            ///< The M key
	        N,            ///< The N key
	        O,            ///< The O key
	        P,            ///< The P key
	        Q,            ///< The Q key
	        R,            ///< The R key
	        S,            ///< The S key
	        T,            ///< The T key
	        U,            ///< The U key
	        V,            ///< The V key
	        W,            ///< The W key
	        X,            ///< The X key
	        Y,            ///< The Y key
	        Z,            ///< The Z key
	        Num0,         ///< The 0 key
	        Num1,         ///< The 1 key
	        Num2,         ///< The 2 key
	        Num3,         ///< The 3 key
	        Num4,         ///< The 4 key
	        Num5,         ///< The 5 key
	        Num6,         ///< The 6 key
	        Num7,         ///< The 7 key
	        Num8,         ///< The 8 key
	        Num9,         ///< The 9 key
	        Escape,       ///< The Escape key
	        LControl,     ///< The left Control key
	        LShift,       ///< The left Shift key
	        LAlt,         ///< The left Alt key
	        LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
	        RControl,     ///< The right Control key
	        RShift,       ///< The right Shift key
	        RAlt,         ///< The right Alt key
	        RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
	        Menu,         ///< The Menu key
	        LBracket,     ///< The [ key
	        RBracket,     ///< The ] key
	        SemiColon,    ///< The ; key
	        Comma,        ///< The , key
	        Period,       ///< The . key
	        Quote,        ///< The ' key
	        Slash,        ///< The / key
	        BackSlash,    ///< The \ key
	        Tilde,        ///< The ~ key
	        Equal,        ///< The = key
	        Dash,         ///< The - key
	        Space,        ///< The Space key
	        Return,       ///< The Return key
	        Back,         ///< The Backspace key
	        Tab,          ///< The Tabulation key
	        PageUp,       ///< The Page up key
	        PageDown,     ///< The Page down key
	        End,          ///< The End key
	        Home,         ///< The Home key
	        Insert,       ///< The Insert key
	        Delete,       ///< The Delete key
	        Add,          ///< +
	        Subtract,     ///< -
	        Multiply,     ///< *
	        Divide,       ///< /
	        Left,         ///< Left arrow
	        Right,        ///< Right arrow
	        Up,           ///< Up arrow
	        Down,         ///< Down arrow
	        Numpad0,      ///< The numpad 0 key
	        Numpad1,      ///< The numpad 1 key
	        Numpad2,      ///< The numpad 2 key
	        Numpad3,      ///< The numpad 3 key
	        Numpad4,      ///< The numpad 4 key
	        Numpad5,      ///< The numpad 5 key
	        Numpad6,      ///< The numpad 6 key
	        Numpad7,      ///< The numpad 7 key
	        Numpad8,      ///< The numpad 8 key
	        Numpad9,      ///< The numpad 9 key
	        F1,           ///< The F1 key
	        F2,           ///< The F2 key
	        F3,           ///< The F3 key
	        F4,           ///< The F4 key
	        F5,           ///< The F5 key
	        F6,           ///< The F6 key
	        F7,           ///< The F7 key
	        F8,           ///< The F8 key
	        F9,           ///< The F8 key
	        F10,          ///< The F10 key
	        F11,          ///< The F11 key
	        F12,          ///< The F12 key
	        F13,          ///< The F13 key
	        F14,          ///< The F14 key
	        F15,          ///< The F15 key
	        Pause,        ///< The Pause key

	        KeyCount      ///< Keep last -- the total number of keyboard keys
	    };
	}
	namespace Mouse{
		enum Button
		{
			Left,
			Right,
			Middle,
			XButton1,
			XButton2,
			ButtonCount
		};
	}
	namespace GameMode{
		enum Mode{
			Salir = 0,
			Menu = 1,
			Strategy = 2,
			Action = 3
		};
	}
	namespace GameActionStatus{
		enum Mode{
			Normal = 0,
			Paused = 1,
			Console = 2,
			GameOver = 3,
			Win = 4,
		};
	}
	const int signalExit = -3;
	namespace Map{
		enum Object{
			Perimeter,
			Wall,
			Table,
			Column,
			Computer,
			Door,
			Player,
			Companion,
			Enemy,

			ObjsCount
		};
	}
	namespace Widget
	{
		enum Type {
			w_none,
			w_button,
			w_label,
			w_radio,
			size
		};
	}
}
#endif /* StracomterNamespace_H_ */
