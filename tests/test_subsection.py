import json
import math

import getkw
import pytest


@pytest.fixture
def subsections():
    return F"""
top {{
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]

sub {{
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]

sub<gorilla> {{
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]
}}
}}
}}
"""


reference = {
    'int': 42,
    'dbl': math.pi,
    'bool': True,
    'str': 'fooffa',
    'int_array': list(range(1, 5)),
    'dbl_array': [math.pi, math.e, math.tau],
    'bool_array': [True, True, True, False, True, False],
    'str_array': ["foo", "bar", "lorem", "IpSuM"]
}


def test_subsection(subsections):
    bnf = getkw.GetkwParser()
    tokens = bnf.parseString(subsections)

    root = tokens.get_topsect()
    top = root.fetch_sect('top')
    sub = top.fetch_sect('sub')
    subgorilla = sub.fetch_sect('sub<gorilla>')
    sections = [top, sub, subgorilla]

    for k, v in reference.items():
        for section in sections:
            assert section.get_keyword(F'{k}').get() == v


#@pytest.fixture
#def empty():
#    return getkw.Section(name="empty")
#
#
#def test_section_empty(empty):
#    print(F'\n{json.dumps(empty, cls=getkw.SectionEncoder, indent=2)}')
#
#
#@pytest.fixture
#def with_keyword():
#    one = getkw.Section(name="one")
#    one.add_kw(name="two", typ="DBL_ARRAY", arg=[0.0, 1.0, 2.0])
#    return one
#
#
#def test_section_with_keyword(with_keyword):
#    print(F'\n{json.dumps(with_keyword, cls=getkw.SectionEncoder, indent=2)}')
#
#
#@pytest.fixture
#def with_section():
#    two = getkw.Section(name="two", tag="foo")
#    ernesto = getkw.Section(name="ernesto", tag="bar")
#    two.add_sect(ernesto)
#    return two
#
#
#def test_section_with_section(with_section):
#    print(F'\n{json.dumps(with_section, cls=getkw.SectionEncoder, indent=2)}')
