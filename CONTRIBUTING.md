# Contributing
Thanks for considering contributing to this project.  
Every contribution is welcome.
A contribution can be a suggestion, a bug report, a feature request or a patch that fixes a bug, makes the code better or improves performance.
You can [email](mailto:mc.cm.mail@gmail.com) them to me directly or submit them at the appropriate place explained in further text.
By default every contributor whose contribution gets approved will be acknowledged in the README.
If you don't wish to be acknowledged, please specify that when submitting your contribution.

## Reporting bugs and adding suggestions
If you find a bug or a behavior that doesn't seem right or you have a suggestion for improving the project, you can report it in the [Issues](../../issues) tab with the appropriate tag.
In the report describe what behavior you observed (screenshots/videos are always helpful), what would you expect to see and how others can recreate the behavior.

## Submitting patches
If you created a bug fix, simplified the code or improved performance, you can create a pull request in the [Pull requests](../../pulls) tab.

### Commit message
The title of the commit message should be descriptive but concise.
It should be in the past simple tense and no longer than 72 characters.
Preferably, the first word should classify the change the commit is making.
For examples see the previous commits titles (`git log --oneline`).  
If further details are need, they should go in the commit message below the title.
The lines in the commit message shouldn't exceed 76 characters.

### Coding conventions
This project tends to follow the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines), though there might be some custom conventions.
Just follow the code around your change and you should be able to infer what they are.

### Bug fix
If you created a patch that fixes the bug, please also submit a description of the bug and how it can be reproduced.

### Code style change
If you find that some part of the code can be simplified or reorganized in a better way without negatively affecting it's runtime you can submit this a style change patch.

### Performance improvements
If you are submitting a patch that improves the performance, please also submit the results of the testing/benchmark you've done to confirm the improvement, a description of the environment you are running and a procedure detailing how this process can be potentially reproduced.
