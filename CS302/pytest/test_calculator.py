import pytest
import calculator as c

def test_print_message():
    test_message: str = "Hello World"

    assert c.print_message(test_message) == f"Message: {test_message}" 
    assert type(c.print_message(test_message)) is str

def test_to_make_sure_that_the_addition_function_add_works_and_that_there_cannot_be_negative_values():
    # Normal values check:
    x: int = c.add(0,1)
    assert x == 1

    # Not negative
    y: int = c.add(-1, -5)
    assert y == 0

@pytest.fixture
def person_obj():
    person = c.Person("Leah", 23)
    return person

def test_to_make_sure_I_can_get_the_name_and_age(person_obj):
    assert person_obj.get_name() == "Leah"
    assert person_obj.get_age() == 23

def test_other_things_if_I_want_to_the_person_is_the_same(person_obj):
    pass

def test_that_always_fails():
    assert 1 == 0