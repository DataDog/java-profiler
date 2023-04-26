import sys
from bs4 import BeautifulSoup

def remove_tags(soup, tags_to_remove):
    for tag in tags_to_remove:
        for element in soup.find_all(tag):
            element.decompose()