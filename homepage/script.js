const Christ = document.getElementById("Christ") || null;
const is = document.getElementById("is") || null;
const King = document.getElementById("King") || null;
const up = document.getElementById("updir") || null;
const upup = document.getElementById("updir-2") || null;
const upupup = document.getElementById("updir-3") || null;

function highlightChrist() {
	Christ?.classList.add("highlight");
	is?.classList.remove("highlight");
	King?.classList.remove("highlight");
}

function highlightUp() {
	up?.classList.add("highlight");
	upup?.classList.remove("highlight");
	upupup?.classList.remove("highlight");
}

function highlightChristAndIs() {
	Christ?.classList.add("highlight");
	is?.classList.add("highlight");
	King?.classList.remove("highlight");
}

function highlightUpUp() {
	up?.classList.add("highlight");
	upup?.classList.add("highlight");
	upupup?.classList.remove("highlight");
}

function highlightAll() {
	Christ?.classList.add("highlight");
	is?.classList.add("highlight");
	King?.classList.add("highlight");
}

function highlightBackAll() {
	up?.classList.add("highlight");
	upup?.classList.add("highlight");
	upupup?.classList.add("highlight");
}

function removeHighlight() {
	Christ?.classList.remove("highlight");
	is?.classList.remove("highlight");
	King?.classList.remove("highlight");
}

function removeHighlightBackAll() {
	up?.classList.remove("highlight");
	upup?.classList.remove("highlight");
	upupup?.classList.remove("highlight");
}

Christ?.addEventListener("mouseover", highlightChrist);
Christ?.addEventListener("mouseleave", removeHighlight);
up?.addEventListener("mouseover", highlightUp);
up?.addEventListener("mouseleave", removeHighlightBackAll);

is?.addEventListener("mouseover", highlightChristAndIs);
is?.addEventListener("mouseleave", removeHighlight);
upup?.addEventListener("mouseover", highlightUpUp);
upup?.addEventListener("mouseleave", removeHighlightBackAll);

King?.addEventListener("mouseover", highlightAll);
King?.addEventListener("mouseleave", removeHighlight);
upupup?.addEventListener("mouseover", highlightBackAll);
upupup?.addEventListener("mouseleave", removeHighlightBackAll);
