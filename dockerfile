# Usa una imagen base de Ubuntu
FROM ubuntu:22.04

# Instala las dependencias necesarias
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    libomp-dev \
    nano \
    openmpi-bin \
    libopenmpi-dev

# Configura las variables de entorno para MPI
ENV PATH="/usr/lib/openmpi/bin:${PATH}"

# Crea un directorio de trabajo dentro del contenedor
WORKDIR /usr/src/app

# Monta un volumen para que puedas persistir archivos
VOLUME /usr/src/app

# Configura el punto de entrada para el contenedor
CMD ["bash"]
