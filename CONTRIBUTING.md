# Contributing Guidelines

To ensure a high quality of code and maintain a clean history, please follow the guidelines below.


## Branch Naming Convention

We use a structured naming convention to keep our git tree organized.

```
State-Part-Description
```

- **State**: The type of change
- **Part**: The main module (e.g., GAME, NETWORK, ECS)
- **Description**: Short, descriptive summary in lowercase

### Format

| Type       | Description                                                  |
|------------|--------------------------------------------------------------|
| feature    | A new feature                                                |
| fix        | A bug fix                                                    |
| refactor   | Code change that neither fixes a bug nor adds a feature      |
| docs       | Documentation only changes                                   |

### Examples

- feature-NETWORK-tcp-connection
- fix-GAME-player-movement
- docs-ECS-component-documentation

## Commit Message Convention

We use the Conventional Commit specification:

```
type(scope): description
```

- **state**: The type of change (see table below)
- **scope**: The part of the codebase affected
- **description**: short summary in imperative

### Format

| Type       | Description                                                  |
|------------|--------------------------------------------------------------|
| feat       | A new feature                                                |
| fix        | A bug fix                                                    |
| refactor   | Code change that neither fixes a bug nor adds a feature      |
| docs       | Documentation only changes                                   |
| perf       | Performance improvements                                     |
| ci         | Changes to CI/CD configuration                               |
| chore      | Change build configuration                                   |

### Examples 

- feat(ECS): add component layer
- refactor(README): removing useless docs 

## C++ Coding Standards

### General Rules
- Language Standard: C++20.
- File Encoding: UTF-8.
- Indentation: 4 spaces (no tabs).

### Naming Convention

| Element           | Style                   | Example                      |
|-------------------|-------------------------|------------------------------|
| Classes/Structs   | PascalCase              | NetworkManager               |
| Methods/Functions | camelCase               | getSize                      |
| Variables         | camelCase               | idComponent                  |
| Member Variables  | `_` prefix + camelCase  | _idComponent                 |
| namespaces        | snake_case              | ntw                          |


# Thank you for contributing