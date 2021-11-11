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


if __name__ == '__main__':
    args = process_args()
    str1, str2 = args.strings

    levenshtein_distance = naive_levenshtein(str1, str2)
    print(f"lev({str1}, {str2}) = {levenshtein_distance}")
