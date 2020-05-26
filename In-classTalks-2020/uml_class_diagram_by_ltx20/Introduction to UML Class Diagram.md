## Introduction to UML Class Diagram

#### Description

- [UML](https://en.wikipedia.org/wiki/Unified_Modeling_Language) (Unified Modeling Language): Provides standard to visualize the process of modeling. 

- [UML Class Diagram](https://en.wikipedia.org/wiki/Class_diagram): Describes relationships between classes and the structure of a program using simple symbols. Can be easily translated into real code.

#### Notation

###### Represent classes

We draw a box with three compartments to describe a class. 

![example](1.png)

- The name is written in the top compartment.
- Member variables are written in the middle compartment.
- Member functions are written in the bottom compartment.

We use `+` for public, `-` for private, and `#` for protected. They should be placed before the name of variables and functions. Static members are underlined.

###### Represent relationships

Different logical connections are shown by 6 types of arrows.

![example](2.png)

- Aggregation and composition: They all correspond to the "has a" relationship, which usually appears as member variable composition in real code. The arrow points to the containing class from the contained class. If the content has a strong lifecycle dependency on the container (doesn't exist after the container is destroyed), then it's called composition. Otherwise, it's aggregation.
- Inheritance and realization: They represent the "is a" relationship, which is usually implemented by inheritance in real code. The arrow points to the base class from the subclass. The difference is that realization inherits abstract classes.

- Association: It means the two classes have a natural relationship, such as ownership and visibility. Most of the time it's bi-directional.
- Dependency: Instead of association, dependency describes the relationship while running the program. For example, if one class needs to use data of the other class, then it's called dependency.

#### Tool

[PlantUML](https://github.com/plantuml/plantuml): An open-source component to draw UML diagrams.