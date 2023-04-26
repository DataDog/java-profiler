import sys
from bs4 import BeautifulSoup

from python_utils import remove_tags

if __name__ == "__main__":
    input_file = sys.argv[1]

    with open(input_file, "r") as file:
        html_content = file.read()

    soup = BeautifulSoup(html_content, "html.parser")
    remove_tags(soup, ["title", "style", "head"])

    print(str(soup))
