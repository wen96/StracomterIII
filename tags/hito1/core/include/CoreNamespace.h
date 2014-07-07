#ifndef StracomterNamespace_H_
#define StracomterNamespace_H_

/** Namespace para variables globales y tipos en el core
 */
namespace Core {
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

				size = 13};       //!< size: Total de tipos, cambiar si aparecen mas
	};
	namespace Key{
	enum Code
	    {
	        A = 'a',
	        B = 'b',
	        C = 'c',
	        D = 'd',
	        E = 'e',
	        F = 'f',
	        G = 'g',
	        H = 'h',
	        I = 'i',
	        J = 'j',
	        K = 'k',
	        L = 'l',
	        M = 'm',
	        N = 'n',
	        O = 'o',
	        P = 'p',
	        Q = 'q',
	        R = 'r',
	        S = 's',
	        T = 't',
	        U = 'u',
	        V = 'v',
	        W = 'w',
	        X = 'x',
	        Y = 'y',
	        Z = 'z',
	        Num0 = '0',
	        Num1 = '1',
	        Num2 = '2',
	        Num3 = '3',
	        Num4 = '4',
	        Num5 = '5',
	        Num6 = '6',
	        Num7 = '7',
	        Num8 = '8',
	        Num9 = '9',
	        Escape = 256,
	        LControl,
	        LShift,
	        LAlt,
	        LSystem,      ///< OS specific key (left side) : windows (Win and Linux), apple (MacOS), ...
	        RControl,
	        RShift,
	        RAlt,
	        RSystem,      ///< OS specific key (right side) : windows (Win and Linux), apple (MacOS), ...
	        Menu,
	        LBracket,     ///< [
	        RBracket,     ///< ]
	        SemiColon,    ///< ;
	        Comma,        ///< ,
	        Period,       ///< .
	        Quote,        ///< '
	        Slash,        ///< /
	        BackSlash,
	        Tilde,        ///< ~
	        Equal,        ///< =
	        Dash,         ///< -
	        Space,
	        Return,
	        Back,
	        Tab,
	        PageUp,
	        PageDown,
	        End,
	        Home,
	        Insert,
	        Delete,
	        Add,          ///< +
	        Subtract,     ///< -
	        Multiply,     ///< *
	        Divide,       ///< /
	        Left,         ///< Left arrow
	        Right,        ///< Right arrow
	        Up,           ///< Up arrow
	        Down,         ///< Down arrow
	        Numpad0,
	        Numpad1,
	        Numpad2,
	        Numpad3,
	        Numpad4,
	        Numpad5,
	        Numpad6,
	        Numpad7,
	        Numpad8,
	        Numpad9,
	        F1,
	        F2,
	        F3,
	        F4,
	        F5,
	        F6,
	        F7,
	        F8,
	        F9,
	        F10,
	        F11,
	        F12,
	        F13,
	        F14,
	        F15,
	        Pause,

	        Count // Keep last -- total number of keyboard keys
	    };
	}
}
#endif /* StracomterNamespace_H_ */
