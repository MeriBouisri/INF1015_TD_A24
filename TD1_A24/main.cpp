/*
 * TD1 - Automne 2024
 *
 * INF1015 - Programmation orientee objet avancee
 * TD #1
 * \date 11/09/2024
 * \author BOUISRI Merieme, 2393471
 * \author XA Jason, 2348245
 */

#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

static const std::string INPUT_GRADES_PATH = "./resources/notes.txt";
static const std::string OUTPUT_GRADES_PATH = "./evaluation.txt";
static const double WEIGHT_GRADE_INTRA = 0.3;
static const double WEIGHT_GRADE_LABS = 0.3;
static const double WEIGHT_GRADE_FINAL = 0.4;
static const char NOTES_DELIMITER = ' ';

namespace math {

	static bool isDivider(int n, int d) {
		return n % d == 0;
	}

	static bool isPrime(int n) {
		for (int i = 2; i < std::sqrt(n); i++)
			if (isDivider(n, i))
				return false;

		return true;
	}

	static std::vector<int> getDividers(int n) {

		std::vector<int> dividers = {};

		// Check special case
		if (n == 2)
			return dividers;

		for (int i = 2; i <= n; i++)
			if (isDivider(n, i))
				dividers.push_back(i);

		return dividers;
	}

	static std::vector<std::string> splitString(std::string str, char delimiter) {
		size_t offset = 0;
		std::vector<std::string> tokens;

		// using do-while to get the last token
		do {
			offset = str.find(delimiter);

			while (str[offset + 1] == delimiter)
				offset++;

			tokens.push_back(str.substr(0, offset));
			str = str.substr(offset + 1);

		} while (offset != std::string::npos);

		return tokens;
	}

}

struct Student {
	std::string matricule = "";
	double gradeIntra = 0.0;
	double gradeLabs = 0.0;
	double gradeFinal = 0.0;



	/**
	 * @brief Enum class to represent the different types of data in the class data file
	 * The order of the values in the enum class must match the order of the data in the file
	 */
	enum class DataPosition {
		MATRICULE,
		NOTE_INTRA,
		NOTE_LABS,
		NOTE_FINAL
	};

	double getStudentAverage() {
		return Student::getStudentAverage(*this);
	}

	static double getStudentAverage(Student student) {
		return student.gradeIntra * WEIGHT_GRADE_INTRA
			+ student.gradeLabs * WEIGHT_GRADE_LABS
			+ student.gradeFinal * WEIGHT_GRADE_FINAL;
	}

	static Student getStudentWithHighestGrade(std::vector<Student> students, int courseIndex = -1) {
		double grade = 0;
		double bestGrade = 0;
		Student bestStudent;

		for (Student s : students) {
			switch (courseIndex) {

				case int(Student::DataPosition::NOTE_INTRA) :
					grade = s.gradeIntra;
					break;

					case int(Student::DataPosition::NOTE_LABS) :
						grade = s.gradeLabs;
						break;

						case int(Student::DataPosition::NOTE_FINAL) :
							grade = s.gradeFinal;
							break;

						default:
							grade = s.getStudentAverage();

			}

			if (grade > bestGrade) {
				bestGrade = grade;
				bestStudent = s;
			}
		}

		return bestStudent;
	}

	static double getClassAverage(std::vector<Student> students) {
		double sum = 0.0;

		for (Student s : students)
			sum += s.getStudentAverage();

		return sum / students.size();
	}


	static std::vector<Student> deserializeClassData(std::vector<std::string> classData) {
		std::vector<Student> students(classData.size());

		for (int i = 0; i < classData.size(); i++) {

			std::vector<std::string> studentData = math::splitString(classData[i], NOTES_DELIMITER);

			Student student = {
				studentData[int(Student::DataPosition::MATRICULE)],
				std::stod(studentData[int(Student::DataPosition::NOTE_INTRA)]),
				std::stod(studentData[int(Student::DataPosition::NOTE_LABS)]),
				std::stod(studentData[int(Student::DataPosition::NOTE_FINAL)])
			};

			students[i] = student;
		}

		return students;
	}

	static std::vector<std::string> readClassDataLines(std::string filename) {
		std::ifstream file(filename);
		std::string line;
		std::vector<std::string> lines;

		if (!file.is_open())
			std::cerr << "[ERREUR] Fichier introuvable : " << filename << "\n";

		else
			while (std::getline(file, line))
				lines.push_back(line);

		return lines;
	}

};

// ==========
// EXERCISE 1
// ==========

static void exercise1() {
	int n;
	double sum = 0;

	std::cout << "Entrez un entier: ";
	std::cin >> n;

	for (int k = 1; k <= n; k++) {
		sum += 1.0 / k;
	}


	std::cout << "Le plus petit entier a tel que Sn <= a est " << int(sum);
}

static std::string rotateString(std::string charString, int n, bool val) {
	if (val) {
		n = -abs(n) + int(charString.length());
	}
	else {
		n = abs(n);
	}

	std::rotate(charString.begin(), charString.begin() + n, charString.end());
	return charString;
}

// ==========
// EXERCISE 3
// ==========

static void exercise3() {
	std::string charString;
	int n;
	bool val;

	std::cout << "Entrez une charString de caracteres: ";
	std::cin >> charString;
	std::cout << "Entrez un nombre entre 1 et " << charString.length() << " : ";
	std::cin >> n;
	std::cout << "Entrez une valeur booleenne (1 ou 0): ";
	std::cin >> val;

	std::cout << "charString=" << charString << " , n=" << n << ", val=" << val << " --> resultat=" << rotateString(charString, n, val);
}

static int deleteDuplicates(int n, int intArray[]) {
	int index[1001] = {};

	for (int i = 0; i < n; i++) {
		index[intArray[i]]++;
		if (index[intArray[i]] > 1) {
			for (int j = i; j < n; j++) {
				intArray[i] = intArray[i + 1];
			}
			n--;
		}
	}
	return n;
}

// ==========
// EXERCISE 5
// ==========

static void exercise5() {
	int n;

	std::cout << "Entrez la taille du tableau (0-1000): ";
	std::cin >> n;

	int intArray[1000] = {};

	for (int i = 0; i < n; i++) {
		std::cout << "Entrez la valeur entiere a la position " << i << " du tableau: ";
		std::cin >> intArray[i];
	}

	int newN = deleteDuplicates(n, intArray);

	std::cout << "[";
	for (int k = 0; k < newN; k++) {
		std::cout << intArray[k];
		if (k < newN - 1) { std::cout << ", "; }
	}
	std::cout << "]";
}

// ==========
// EXERCICE 2
// ==========


/**
* @brief Function to get user input for exercise 2.
* @param isValidNum std::function function to determine condition to validate the input
* @return int the number entered by the user
*/
static int inputMessageExercise2(std::function<bool(int)> isValidNum) {
	int num = 0;

	while (!num) {

		std::cout << "Entrez un entier plus grand ou egal a 2 (n >= 2)\nn = ";
		std::cin >> num;

		if (isValidNum(num))
			break;

		std::cout << "Erreur: n doit etre plus grand ou egal a 2\n";
		num = 0;
	}

	return num;
}

/**
* @brief Function to output the result of exercise 2
* @param num int the number entered by the user
* @param dividers std::vector<int> the dividers of the number
*/
static void outputMessageExercise2(int num, std::vector<int> dividers) {
	// prime = no dividers
	if (dividers.empty()) {
		std::cout << "Le nombre " << num << " est premier\n";
		return;
	}

	std::cout << "Les diviseurs de " << num << " sont: ";

	for (int i = 0; i < dividers.size(); i++)
		std::cout << (i == 0 ? "" : ", ") << dividers[i];

	std::cout << "\n";
}


static void exercise2() {

	int num = inputMessageExercise2(
		[](int n) { return n >= 2; });

	outputMessageExercise2(num, math::getDividers(num));
}

// ==========
// EXERCICE 4
// ==========

static void exercise4() {

	int realNum, guessNum;
	int tries = 0;

	std::cout << "Entrez un entier a deviner : ";
	std::cin >> realNum;

	while (true) {
		tries++;

		std::cout << "Devinez le nombre choisi : ";
		std::cin >> guessNum;

		if (guessNum == realNum)
			break;

		std::cout << "Echoue.\nLe nombre r�el est "
			<< (realNum > guessNum
				? "superieur"
				: "inferieur")
			<< " a votre choix.\n";
	}

	std::cout << "Succes.\nTentatives : " << tries;
}

// ==========
// EXERCISE 6
// ==========

static void exercise6() {

	std::vector<std::string> classData = Student::readClassDataLines(INPUT_GRADES_PATH);
	size_t numStudents = classData.size();

	std::vector<Student> students = Student::deserializeClassData(classData);

	// Output to file

	std::ofstream file;
	file.open(OUTPUT_GRADES_PATH);

	if (!file.is_open()) {
		std::cerr << "[ERREUR] Impossible de creer le fichier : " << OUTPUT_GRADES_PATH << "\n";
		return;
	}

	file << "La moyenne de la classe est : " << Student::getClassAverage(students) << std::endl;

	Student bestStudent = Student::getStudentWithHighestGrade(students, int(Student::DataPosition::NOTE_LABS));
	file << "L'etudiant ayant le matricule "
		<< bestStudent.matricule
		<< " a la meilleure note "
		<< bestStudent.gradeLabs
		<< " dans les labs" << std::endl;

	bestStudent = Student::getStudentWithHighestGrade(students);
	file << "L'etudiant ayant le matricule "
		<< bestStudent.matricule
		<< " a la meilleure moyenne "
		<< Student::getStudentAverage(bestStudent)
		<< " dans l'ensemble des cours" << std::endl;

	std::cout << "[SUCCES] Evaluation des notes ecrites dans le fichier : " << OUTPUT_GRADES_PATH << std::endl;
}

// ====
// MAIN
// ====


int main() {

	while (true) {

		std::cout << "\nChoisissez un exercice (1-6) : " << std::endl;
		int choice;
		bool exit = false;

		std::cin >> choice;

		switch (choice) {


		case 1:
			exercise1();
			break;

		case 2:
			exercise2();
			break;

		case 3:
			exercise3();
			break;

		case 4:
			exercise4();
			break;

		case 5:
			exercise5();
			break;

		case 6:
			exercise6();
			break;

		default:
			std::cout << "Choix invalide" << std::endl;
			break;
		}
	}

}