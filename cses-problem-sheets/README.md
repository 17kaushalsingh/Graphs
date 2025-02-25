# C++ Development Environment Using Docker


## Build the image
```sh
docker build -t cpp-env .
```

## Create the container
```sh
docker run --name cpp-env -it -v /Users/kaushal/Github/placements-2025/cses-problem-set:/usr/workspace cpp-env
```

## Start the container
```sh
docker start cpp-env
```

## Stop the container
From inside the container:
```sh
exit
```
From outside the container:
```sh
docker stop cpp-env
```