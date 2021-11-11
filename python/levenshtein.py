import argparse


def process_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--strings', '-s', nargs=2, required=True,
                        help='strings to determine the Levenshtein distance of')
    return parser.parse_args()


def naive_levenshtein(a: str, b: str):
    if len(a) == 0:
        return len(b)
    elif len(b) == 0:
        return len(a)
    elif a[0] == b[0]:
        return naive_levenshtein(a[1:], b[1:])
    else:
        minimum = min((naive_levenshtein(a[1:], b),
                       naive_levenshtein(a, b[1:]),
                       naive_levenshtein(a[1:], b[1:])))
        return 1 + minimum


def iterative_levenshtein(a: str, b: str):
    """Use the Wagner-Fischer algorithm to determine the Levenshtein distance more efficiently."""
    len_a = len(a)
    len_b = len(b)
    distance_matrix = (len_a + 1) * (len_b + 1) * [0]
    width = len_a + 1
    for i in range(len(distance_matrix)):
        row = i // width
        col = i % width
        if row == 0:
            distance_matrix[i] = col
            continue
        if col == 0:
            distance_matrix[i] = row
            continue

        # delete character from string a
        deletion = distance_matrix[row * width + (col-1)] + 1
        # insert character into string a
        insertion = distance_matrix[(row-1) * width + col] + 1

        # substitute characters
        cost = 0 if a[col-1] == b[row-1] else 1
        substitution = distance_matrix[(row-1) * width + (col-1)] + cost
        distance_matrix[i] = min((deletion, insertion, substitution))

    return distance_matrix[-1]


if __name__ == '__main__':
    args = process_args()
    str1, str2 = args.strings

    levenshtein_distance = naive_levenshtein(str1, str2)
    print(f"recursive: lev({str1}, {str2}) = {levenshtein_distance}")

    iterative_levenshtein_distance = iterative_levenshtein(str1, str2)
    print(f"iterative: lev({str1}, {str2}) = {iterative_levenshtein_distance}")
