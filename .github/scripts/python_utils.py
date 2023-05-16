import sys
from bs4 import BeautifulSoup

def remove_tags(soup, tags_to_remove):
    for tag in tags_to_remove:
        for element in soup.find_all(tag):
            element.decompose()

def create_scanbuild_code_links(soup, target_branch):
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
def parse_table(table):
    markdown_table = []
    for row in table.find_all('tr'):
        cells = row.find_all(['th', 'td'])
        markdown_cells = [cell.get_text(strip=True) for cell in cells]
        markdown_table.append('| ' + ' | '.join(markdown_cells) + ' |')
    return '\n'.join(markdown_table)

def scanbuild_cleanup(soup, args):
    target_branch = args[0]
    remove_tags(soup, ["title", "script", "a"])
    create_scanbuild_code_links(soup, target_branch)
    title = soup.find('h1')
    title.string = 'Scan-Build Report'
    return str(soup)

def cppcheck_cleanup(soup, args):
    remove_tags(soup, ["title", "style", "head"])
    return str(soup)

def usage(soup, args):
    return "Usage"

if __name__ == "__main__":
    actions = {
        "scanbuild_cleanup": scanbuild_cleanup,
        "cppcheck_cleanup": cppcheck_cleanup,
    }
    action = actions.get(sys.argv[1], usage)
    input_file = sys.argv[2]
    args = sys.argv[3:]

    with open(input_file, "r") as file:
        html_content = file.read()

    soup = BeautifulSoup(html_content, "html.parser")
    print(action(soup, args))
