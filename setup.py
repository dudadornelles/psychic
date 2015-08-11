from setuptools import setup, find_packages

setup(
        name='psychic',
        version='0.0.1',
        description='Unit testing library for C - powered by python',
        url='https://github.com/dudadornelles/tcc',
        author='Duda Dornelles',
        author_email='dudassdornelles@gmail.com',
        license='MIT',
        keywords='c unit test',
        packages=find_packages(exclude=['contrib', 'docs', 'tests*']),
        entry_points={
            'console_scripts': [
                'psychic=psychic:main',
            ],
        },
)

