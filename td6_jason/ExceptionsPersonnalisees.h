/**
* Exceptions personnalis�es
* \file   ExceptionsPersonnalisees.h
* \author Bouisri et Xa
* \date   4 d�cembre 2024
* Cr�� le 19 novembre 2024
*/

#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QObject>
#pragma pop()

namespace espaceModele {
	class ExceptionDescriptionVide : public std::invalid_argument {
	public:
		using invalid_argument::invalid_argument;
	};

	class ExceptionPrixNul : public std::invalid_argument {
	public:
		using invalid_argument::invalid_argument;
	};
}
