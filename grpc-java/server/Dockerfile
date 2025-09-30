FROM openjdk:11-jre-slim
WORKDIR /app
COPY target/server-service-jar-with-dependencies.jar server-service.jar
EXPOSE 8081
CMD ["java", "-jar", "server-service.jar"]