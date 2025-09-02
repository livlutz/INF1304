package br.com.meslin;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.common.serialization.StringSerializer;

import java.util.Properties;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ChatProducer {
    private final KafkaProducer<String, String> producer;
    private final String topic;
    private static final Logger logger = LoggerFactory.getLogger(ChatProducer.class);

    public ChatProducer(String topic) {
        Properties props = new Properties();
        props.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, System.getenv("KAFKA_BROKERS"));
        props.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class.getName());
        props.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, StringSerializer.class.getName());
        producer = new KafkaProducer<>(props);
        this.topic = topic;
    }

    public void sendMessage(String message) {
        message = new Date() + " ==> " + message;
        producer.send(new ProducerRecord<>(topic, message));
    }

    public void close() {
        producer.close();
    }

    public static void main (String[] args) {
        ChatProducer chatProducer = new ChatProducer("chat-messages");
        WebSocketServer.startServer(chatProducer);
        // Keep the application running
        Runtime.getRuntime().addShutdownHook(new Thread(()->{
            WebSocketServer
            .stopServer();
            chatProducer
            .close();
        }));

        try{
            // Use a synchronized block to wait indefinitely
            synchronized(ChatProducer.class) {
                ChatProducer.class.wait();
            }
        }

        catch(InterruptedException e) {
            Thread.currentThread().interrupt();
        }

    }
}
