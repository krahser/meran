FROM debian:squeeze


# Para construir esta imagen se necesita un servidos de mysql o mariadb
# con contraseña de administrador.

RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get update -qq && apt-get install -yqq \
    git-core\
    expect\
    cron\
    supervisor\
    locales

ADD archivos/ssl.sh /opt/ssl.sh
ADD archivos/supervisord.conf /etc/supervisor/conf.d/supervisord.conf
ADD archivos/locale.gen /etc/locale.gen
RUN locale-gen

WORKDIR /opt
RUN git clone https://github.com/Desarrollo-CeSPI/meran.git meran

WORKDIR /opt/meran/docs/generacionInstalador
RUN ./new_instalador.sh

WORKDIR /opt
RUN tar xzf /opt/meran/docs/generacionInstalador/aux/meranunlp-v0.10.5.tar.gz

WORKDIR /opt/meranunlp
RUN chmod +x instalar.sh

WORKDIR /opt/meranunlp
