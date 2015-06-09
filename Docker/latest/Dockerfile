FROM krahser/meran:base

RUN ./instalar.sh -i Oesterheld -N -B1 -P pal4br4S3cr3t4 -h 172.17.42.1
RUN expect /opt/ssl.sh

RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*


#Logs de meran
VOLUME /var/log/meran
EXPOSE 80 443

CMD /usr/bin/supervisord
