FROM gcc:12.2.0

WORKDIR /usr/src/app

RUN apt-get -qq update \
    && apt-get -qq install --no-install-recommends cmake \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# switch master to main -> it work
RUN git clone --depth=1 -b main https://github.com/google/googletest.git
RUN mkdir googletest/build

WORKDIR /usr/src/app/googletest/build

RUN cmake .. \
    && make \
    && make install \
    && rm -rf /usr/src/app/googletest

WORKDIR /usr/src/app

COPY . .
RUN mkdir obj

RUN make

CMD [ "./main" ]
