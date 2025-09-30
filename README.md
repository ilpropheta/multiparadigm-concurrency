# Multiparadigm Concurrency with SObjectizer - Demo Repository

This repository contains demo code from my talk **Multiparadigm Concurrency with SObjectizer**.

📑 Slides are available [here](multiparadigm-concurrency-with-sobjectizer--marco-arena.pdf).

## Experiment on your own

Each chapter of the talk has a corresponding tag in this repository, so you can follow the development step by step just as it was presented.  

For example, the tag [chapter-2](https://github.com/ilpropheta/multiparadigm-concurrency/tree/chapter-2) brings the codebase to the state it reached at the end of Chapter 2.

Feel free to extend this demo by creating new agents and exploring different concurrency setups. Here are a few ideas to get started:

- **Face Detector**: overlays a rectangle on detected faces ([spoiler](https://github.com/ilpropheta/calico/blob/main/calico/agents/face_detector.h))
- **FPS Estimator**: measures frame rate in a channel (e.g. count received frames over a fixed interval such as 10s)
- **Scaler**: resizes each frame by a given scale factor.

You can also try combining these agents to build different pipelines. For instance, the **FPS Estimator** can give you a rough sense of overhead. Try alternative threading models to see how they affect performance.

### Dependencies

This project is configured for **Visual Studio 2022**, but it can be easily ported to **CMake**.  

Required dependencies:
- [OpenCV](https://opencv.org/)
- [SObjectizer](https://github.com/Stiffstream/sobjectizer)

For a quick and straightforward setup, you can use [vcpkg](https://vcpkg.io/en/):

```powershell
vcpkg install opencv --triplet x64-windows
vcpkg install sobjectizer --triplet x64-windows
```

## Intrigued? SObjectizer Tales

If you're interested in the full story behind this talk, check out my 30-article blog series [SObjectizer Tales](https://marcoarena.wordpress.com/sobjectizer-tales/) on developing concurrent applications with SObjectizer.

The project featured in the series, [calico](https://github.com/ilpropheta/calico), is very similar to this demo and already includes a CMake build setup for cross-platform development, and also a docker image for building.