import json
import math

import getkw
import pytest


@pytest.fixture
def keywords():
    return F"""
int = 42
dbl = {math.pi}
bool = on
str = "fooffa"

int_array = {list(range(1, 5))}
dbl_array = [{math.pi}, {math.e}, {math.tau}]
bool_array = [on, true, yes, False, True, false]
str_array = [foo, bar, "lorem", "IpSuM"]
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


def test_keyword(keywords):

    bnf = getkw.GetkwParser()
    tokens = bnf.parseString(keywords)

    for k, v in reference.items():
        assert tokens.get_keyword(F'{k}').get() == v


#def test_keyword_json():
#    key_int_array = getkw.Keyword(name="foo", typ="INT_ARRAY", arg=[0, 1, 2])
#    key_dbl_array = getkw.Keyword(name="bar", typ="DBL_ARRAY", arg=[0.0, 1.0, 2.0])
#
#    print(F'\n{json.dumps(key_int_array, cls=getkw.KeywordEncoder, indent=2)}')
#    print(F'\n{json.dumps(key_dbl_array, cls=getkw.KeywordEncoder, indent=2)}')
