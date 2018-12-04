import json
import math

import getkw
import pytest


@pytest.fixture
def sections():
    return F"""
defs {{
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]
}}

defs<apa> {{
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]
}}

defs<gorilla> {{
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]
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


def test_section(sections):
    bnf = getkw.GetkwParser()
    tokens = bnf.parseString(sections)

    for k, v in reference.items():
        for section in ['defs', 'defs<apa>', 'defs<gorilla>']:
            assert tokens.get_keyword(F'{section}.{k}').get() == v


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
