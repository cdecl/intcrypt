
main.class : main.java
	javac -cp .:jna.jar main.java

clean:
	rm -rf main.class
