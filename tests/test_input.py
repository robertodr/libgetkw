import pytest


@pytest.fixture
def input_str():
    return """
title = foo
string="fooo bar"

defs {
foo=[1,2,3]
bar=99.0
}

defs<apa> {
foo=[1, 2, 3,
4,5, 6,7,8,9,
10]
bar=22.0
}

defs<gorilla> {
foo=[1, 2, 3,
4,5, 6,7,8,9,
10]
bar=22.0
}

verbose=False #(yes|true|on|1)
"""


def test(input_str):
    import getkw
    import pyparsing
    bnf = getkw.GetkwParser()
    try:
        tokens = bnf.parseString(input_str)
    except pyparsing.ParseException as err:
        print((err.line))
        print((" " * (err.column - 1) + "^"))
        print(err)
    #print(tokens.top)
    assert tokens.get_keyword('defs.foo').get() == [1, 2, 3]
    #print('defs.foo is', tokens.get_keyword('defs.foo').get())
    return tokens


#if __name__ == '__main__':
#    ini = test(teststr)
#    print((ini.top))
#    foo=ini.get_keyword('raboof.foo')
#    print dir(foo)
