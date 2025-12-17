# Advent of Code in C++

Using the AoC 2025 as an opportunity to revisit and hone my C++ skills. Haven't used it for a year, good to be back!

## GOALS

I choose to specify my goals before starting, since I believe narrowing down objectives really helps me focus and deep dive.

The goal is to leverage native C++ as much as possible. Rather then exploring the ecosystem and learning frameworks and libraries, I want to learn C++.
Acknowledging that in reality I would be using libraries for say Matrix operations or Graph algorithms, the goal here is to learn about C++, the sources of good resources and C++ documentation.

An alternate goal, is improved algorithmic thinking, better reasoning skills and problem solving (which AoC is ideal for), which align well with my original goal, since I won't be able to rely on existing implementations.

## Lessons Learned

For matrix-like indexing, operations and computations, not relying on existing libraries is demanding. Ideally, one would construct a class with appropriate operators and methods for the use case, and implement contiguous array indexing for optimized performance.

For now, I decided to drop row-major indexing into contiguous arrays, since performance optimization does not align with my goals, but rather seem as a distraction from algorithmic thinking.

Even so, I may revisit multi-dimensional indexing problems and rewrite these as an exercise in both optimization and C-like thinking about spatial and temporal locality.
