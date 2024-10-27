import math


def main() -> None:
    text: str = get_input_text()
    words: float = count_words(text)
    sentences: float = count_sentences(text)
    letters: float = count_letters(text)

    l: float = (letters / words) * 100
    print(l)
    s: float = (sentences / words) * 100
    print(s)
    index: float = (0.0588 * l) - (0.296 * s) - 15.8

    print(index)

    get_rating(index)


def get_rating(index: float) -> None:
    round_index: int = round(index)
    if round_index < 1:
        print("Before Grade 1")
    elif round_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round_index)}")


def count_letters(input: str) -> int:
    letter_count: int = 0
    for char in input:
        # sum(1 for char in input if char.isalpha()) one liner
        if char not in [" ", ".", "?", "!", ",", ";"]:
            letter_count += 1

    print(letter_count, "letters count")
    return letter_count


def count_words(input: str) -> int:
    word_count: int = sum(1 for char in input if char in [" ", "'"]) + 1
    print(word_count, "words count")
    return word_count


def count_sentences(input: str) -> int:
    sentence_count: int = sum(1 for char in input if char in ["!", ".", "?"])
    print(sentence_count, "sentences count")
    return sentence_count


def get_input_text() -> str:
    text: str = """It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him."""
    while True:
        try:
            user_text: str = input("Text: ")
            if len(user_text) > 0:
                break
        except ValueError:
            print("Something went wrong!")
    return user_text
    # return text


main()
