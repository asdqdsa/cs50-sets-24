const buttonOne = document.getElementById("choice-1");
const multiBlockQuestion = document.getElementById("multi-block");
const freeFormQuestion = document.getElementById("free-form");
const multiFeedback = document.getElementById("result-multi-block");
const freeFeedback = document.getElementById("result-free-form");

const handleButtonClick = (e) => {
	handleResetStyle();
	if (e.target.classList.contains("choice")) {
		if (checkAnswerMulti(e.target.id)) {
			showTooltip(true, multiFeedback);
			setElementStyle(e.target, true);
		} else {
			showTooltip(false, multiFeedback);
			setElementStyle(e.target, false);
		}
	}
};

const handleResetStyle = () => {
	const buttons = document.querySelectorAll(".choice");
	buttons.forEach((button) => {
		button.classList.remove("correct-btn", "incorrect-btn");
	});
};

const setElementStyle = (element, isCorrect) => {
	if (isCorrect) element.classList.add("correct-btn");
	else element.classList.add("incorrect-btn");
};

const showTooltip = (isAnswerRight, element) => {
	if (isAnswerRight) {
		element.classList.remove("incorrect-answer");
		element.textContent = "Correct!";
		element.classList.add("correct-answer");
	} else {
		element.classList.remove("correct-answer");
		element.textContent = "Incorrect";
		element.classList.add("incorrect-answer");
	}
	element.classList.add("show");
};

const handleSubmit = (e) => {
	e.preventDefault();
	if (checkAnswerText(e.target.answer.value)) {
		setInputStyle(e.target.answer, true);
		e.target.answer.value = "";
		showTooltip(true, freeFeedback);
		return true;
	} else {
		setInputStyle(e.target.answer, false);
		showTooltip(false, freeFeedback);
		return false;
	}
};

const setInputStyle = (input, isCorrect) => {
	if (isCorrect) input.classList.add("correct-btn");
	else input.classList.add("incorrect-btn");
};

multiBlockQuestion.addEventListener("click", handleResetStyle);
multiBlockQuestion.addEventListener("click", handleButtonClick);

/**
 *
 * @param {string} buttonId - The ID of the button that was clicked
 * @returns {boolean} True if answer is correct
 */
const checkAnswerMulti = (buttonId) => {
	const correctAnswer = "choice-1";
	if (buttonId !== correctAnswer) return false;
	return true;
};

/**
 *
 * @param {string} answer The input field text
 * @returns {boolean} True if answer is correct
 */
const checkAnswerText = (answer) => {
	const correctAnswer = "death";
	if (answer.toLowerCase().trim() !== correctAnswer) return false;
	return true;
};

freeFormQuestion.addEventListener("submit", handleSubmit);

/* 
Answer: death
This phrase was famously spoken by Patrick Henry, a leading figure in the American Revolution, in his speech to the Virginia Convention in 1775. Henry passionately argued that the colonies should fight for independence, stating that living under tyranny was worse than dying for freedom. The phrase has become a symbol of the fight for liberty and the willingness to sacrifice for independence.
*/
