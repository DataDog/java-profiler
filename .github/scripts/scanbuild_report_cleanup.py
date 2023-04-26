import sys
from bs4 import BeautifulSoup

from python_utils import remove_tags

def create_code_links(soup, target_branch):
    target = None
    for element in soup.find_all("td"):
        clz = element.get('class')
        if clz is None:
            src = element.text
            target = element
        elif 'Q' in clz and target is not None and target.text != 'Function/Method':
            line = element.text
            link = soup.new_tag('a', href=f'https://github.com/DataDog/java-profiler-library/blob/{target_branch}/ddprof-lib/src/main/cpp/{src}#L{line}')
            link.string = src
            target.clear()
            target.append(link)
            target = None

if __name__ == "__main__":
    input_file = sys.argv[1]
    target_branch = sys.argv[2]

    with open(input_file, "r") as file:
        html_content = file.read()

    soup = BeautifulSoup(html_content, "html.parser")
    remove_tags(soup, ["title", "script", "a"])
    create_code_links(soup, target_branch)
    title = soup.find('h1')
    title.string = 'Scan-Build Report'
    # TODO consider a link to full report - however, getting a link to GHA artifact within the same workflow seems to be impossible for now

    print(str(soup))
