# <font color="lightgreen"><b>platformX</b></font>
## Introduction to platformX
### What is platformX?
platformX is a cross-platform user interface (UI) framework that helps developers create desktop applications for Windows, macOS, and Linux with a single, unified codebase. Its main goal is to simplify building modern and consistent user interfaces that look and feel native on all major operating systems.

### Why use platformX?
* Simplifies Cross-Platform Development:
    * You write your UI logic once, and platformX takes care of the platform-specific details.
* Consistent Look & Feel:
    * Your apps have a unified UI structure while adapting to native controls and conventions on each OS.
* Organized Project Structure:
    * platformX clearly separates platform-independent UI templates from operating system-specific code, making maintenance and scaling easier.

### How is platformX organized?
Your project using platformX might look like this:

#### System Overview

                        +--------------------------+
                        |        include/          | <-- Platform-independent definitions
                        +--------------------------+
                        | PXApplication            | <-- General application template
                        | PXControl                | <-- General control template
                        | PXControls               | <-- All UI control templates (based on PXControl)
                        | global                   | <-- Global definitions 
                        | util                     | <-- General utility template
                        +--------------------------+
                                      |
            ------------------------------------------------------
            |                         |                          |
    +-------v--------+       +--------v--------+        +--------v-------+
    |  src/windows   |       |   src/macos     |        |  src/linux     | <-- Platform-specific definitions
    |----------------|       |-----------------|        |----------------|
    | window         |       | window          |        | window         | <-- Window logic
    | application    |       | application     |        | application    | <-- Application logic
    | controls       |       | controls        |        | controls       | <-- Common controls logic
    | global         |       | global          |        | global         | <-- Implementation of global functions
    | util           |       | util            |        | util           | <-- Implementation of utility functions
    | ...            |       | ...             |        | ...            |
    +----------------+       +-----------------+        +----------------+

* `PXApplication`
    * The main app logic, shared between all platforms, handling the basic app lifecycle.
* `PXControls`
    * A single file containing all essential UI control templates, such as buttons, group boxes, etc. — these are platform-neutral blueprints.
* `src/<os>/`
    * Folders containing the real code that makes controls work natively on each operating system.

### Key benefits for beginners
* No need to learn each OS’s UI toolkit
    * platformX abstracts away platform complexity, so you can focus on building features, not fighting with Windows, macOS, or Linux APIs.
* Easy to Expand and Maintain
    * Adding new controls is simple — just describe them once and implement small platform-specific files as needed.
* Ideal for Learning
    * The clear separation and templated approach let beginners understand how UI frameworks and cross-platform code organization work.

### Typical workflow
1.	Design your UI controls in `PXControls`.
2.	Write your main application logic in `PXApplication`.
3.	Rely on platformX to connect your templates and app logic to each operating system, so your application builds and runs anywhere.

### In summary
platformX helps new and experienced developers build robust, native-looking desktop apps for multiple operating systems — with less hassle and more code reuse. If you’re new to cross-platform development, platformX offers a friendly starting point for building apps that just work everywhere.

<br><br>

## Using the `ingenity.code-profile`
Code profiles in VS Code let you save and switch between different sets of editor settings, extensions, and UI layouts. This helps you keep project-specific tools and preferences separate, avoiding conflicts. You can quickly set up the ideal environment for different programming languages or workflows. Sharing profiles with teammates ensures everyone works consistently. Profiles also make it easy to experiment with new extensions or settings without messing up your main setup. In short, profiles boost productivity by keeping your VS Code experience organized and tailored to your needs.

#### Loading `ingenity.code-profile` in VS Code
1.	Go to the Command Palette: Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS).
2.	Type "Preferences: Open Profiles (UI)” and select it from the menu.
3.	Browse for the File: Navigate to the location of your `ingenity.code-profile` (in `.vscode` folder).
4.	Select and Confirm: Choose the file and follow the prompts to import. VS Code will apply the settings, extensions, and customizations from the profile.
5.	Restart VS Code (if requested) to activate all changes. Now your VS Code will use the configuration defined in `ingenity.code-profile`. This includes extensions, settings, themes, and layouts tailored for the profile.

<br><br>

## Using code-snippets from `code-profile`
Code snippets in Visual Studio Code are reusable templates that let you quickly insert commonly used code blocks, saving time and reducing errors—especially for repetitive tasks. You can create your own snippets by defining a prefix (the trigger shortcut), a code body (the template), and an optional description in VS Code’s snippet settings.
To use a snippet, type the defined prefix and select it from the suggestions (IntelliSense) or use Insert Snippet from the Command Palette. Placeholders (e.g., `${1:name}`) let you tab through key editing spots after inserting the snippet.

#### The `ingenity.code-profile` currently provides 3 code-snippets, primarily for Windows:
* “PXDUMMY”
    * When you type the trigger for `PXDUMMY` in the header file `include/controls.h`, VS Code will insert your predefined template for this a new UI control.
* “WinDUMMYDef”
    * This snippet, likely for `src/os/controls.h`, can quickly add platform-specific definitions.
* “WinDUMMY”
    * Use this in `src/os/controls.cpp` to insert code for the windows-specific implementation, allowing you to avoid boilerplate typing.

<br><br>

## Building and Running with Bazel 
Getting started with Bazel is simple. Follow these steps to build and run <font color="lightgreen"><b>native_ui_app</b></font> for your platform:

#### 1. Build the Library
Open your terminal and navigate to your project root directory. Then run:

`bazel build //src:platformX`
#### 2. Run the Applicatiopn
`bazel run //:native_ui_app`

### using VSCode tasks
Visual Studio Code (VS Code) lets you automate builds with tasks, defined in `.vscode/tasks.json`. Press Ctrl+Shift+B (or Cmd+Shift+B on Mac) to run the `Tasks: Run Build Task` command, which compiles your project (lib and example-app with debug-symbols). The build step to debugging by using it as a `preLaunchTask` in `launch.json` is implemented, so your code is always built before you debug. This streamlines development by making building and debugging fast and consistent.

<br><br>

## Todo:
### List of controls to be implemented
* Slider (Trackbar)
* Spin (Up-Down)
* Tab
* Header
* Toolbar
* Rich Edit
* Date and Time Picker
* Month Calendar
* IP Address
* Animation
* Hot Key
* Rebar
* Tooltip
* Page Scroller
