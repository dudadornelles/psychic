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
        install_requires=['jinja2'],
        package_data={
            'psychic.csource': ['psychic.h', 'psychic.c', 'psychic_share.h'],
            'psychic': ['testfile.c.jinja'],
            },
        entry_points={
            'console_scripts': [
                'psychic=psychic:main',
            ],
        },
)

