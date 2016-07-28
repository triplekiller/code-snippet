#!/usr/bin/python

class SchoolMember:
    '''Represents any school member.'''
    def __init__(self, name, age):
        self.name = name
        self.age = age
        print('Initializing SchoolMember: {}'.format(self.name))

    def tell(self):
        '''Tell my details.'''
        print('Name:{} Age:{}'.format(self.name, self.age))

class Teacher(SchoolMember):
    '''Represents a teacher.'''
    def __init__(self, name, age, salary):
        SchoolMember.__init__(self, name, age)
        self.salary = salary
        print('Initialzing Teacher: {}'.format(self.name))

    def tell(self):
        SchoolMember.tell(self)
        print('Salary: {:d}'.format(self.salary))

class Student(SchoolMember):
    '''Represents a student.'''
    def __init__(self, name, age, marks):
        SchoolMember.__init__(self, name, age)
        self.marks = marks
        print('Initializing Student: {}'.format(self.name))

    def tell(self):
        SchoolMember.tell(self)
        print('Marks: {:d}'.format(self.marks))

t = Teacher('Mrs Lee', 40, 30000)
s = Student('Ethan', 25, 90)

print("")

members = [t, s]
for member in members:
    member.tell()
