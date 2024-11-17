# Jumbled-Word-Game
This is a console-based jumbled word game build using C programming

# WordCount Hadoop Project

This project demonstrates how to set up a Hadoop environment and implement a simple WordCount application using Java and Hadoop's MapReduce framework. The purpose of the WordCount application is to count the occurrences of each word in a given text file.

## Prerequisites

- Xubuntu (or any Ubuntu-based OS) installed on VirtualBox
- OpenJDK 8
- Hadoop 3.3.6
- Maven
- IntelliJ IDEA

---

## Installation and Configuration

### 1. Installing Java 8

#### Step 1.1: Update the System
Run the following command to update the package manager:
```bash
sudo apt update
```

#### Step 1.2: Install OpenJDK 8
```bash
sudo apt install openjdk-8-jdk
```

Verify the installation:
```bash
java -version
```

#### Step 1.3: Set Up JAVA_HOME
Find the Java path:
```bash
dirname $(dirname $(readlink -f $(which java)))
```

Edit `.bashrc`:
```bash
nano ~/.bashrc
```

Add the following line:
```bash
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
```

Reload the settings:
```bash
source ~/.bashrc
```

---

### 2. Installing Hadoop 3.3.6

#### Step 2.1: Download and Extract Hadoop
```bash
wget https://downloads.apache.org/hadoop/common/hadoop-3.3.6/hadoop-3.3.6.tar.gz
tar -xvzf hadoop-3.3.6.tar.gz
mv hadoop-3.3.6 hadoop
```

#### Step 2.2: Set Up Hadoop Environment Variables
Edit `.bashrc`:
```bash
nano ~/.bashrc
```

Add the following:
```bash
export HADOOP_HOME=~/hadoop
export HADOOP_INSTALL=$HADOOP_HOME
export HADOOP_MAPRED_HOME=$HADOOP_HOME
export HADOOP_COMMON_HOME=$HADOOP_HOME
export HADOOP_HDFS_HOME=$HADOOP_HOME
export HADOOP_YARN_HOME=$HADOOP_HOME
export HADOOP_COMMON_LIB_NATIVE_DIR=$HADOOP_HOME/lib/native
export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin
```

Reload the settings:
```bash
source ~/.bashrc
```

---

### 3. Configuring Hadoop

#### 3.1: Edit `core-site.xml`
```bash
nano ~/hadoop/etc/hadoop/core-site.xml
```

Add:
```xml
<property>
  <name>fs.defaultFS</name>
  <value>hdfs://localhost:9000</value>
</property>
```

#### 3.2: Edit `hdfs-site.xml`
```bash
nano ~/hadoop/etc/hadoop/hdfs-site.xml
```

Add:
```xml
<property>
  <name>dfs.replication</name>
  <value>1</value>
</property>
<property>
  <name>dfs.name.dir</name>
  <value>/home/akb/hadoop/data/namenode</value>
</property>
<property>
  <name>dfs.data.dir</name>
  <value>/home/akb/hadoop/data/datanode</value>
</property>
```

Create directories:
```bash
mkdir -p ~/hadoop/data/namenode
mkdir -p ~/hadoop/data/datanode
```

#### 3.3: Edit `mapred-site.xml`
```bash
nano ~/hadoop/etc/hadoop/mapred-site.xml
```

Add:
```xml
<property>
  <name>mapreduce.framework.name</name>
  <value>yarn</value>
</property>
```

#### 3.4: Edit `yarn-site.xml`
```bash
nano ~/hadoop/etc/hadoop/yarn-site.xml
```

Add:
```xml
<property>
  <name>yarn.nodemanager.aux-services</name>
  <value>mapreduce_shuffle</value>
</property>
<property>
  <name>yarn.nodemanager.auxservices.mapreduce.shuffle.class</name>
  <value>org.apache.hadoop.mapred.ShuffleHandler</value>
</property>
```

---

### 4. Setup SSH
#### Generate SSH Key
```bash
ssh-keygen -t rsa
```

#### Authorize SSH Key
```bash
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 640 ~/.ssh/authorized_keys
```

#### Test SSH
```bash
ssh localhost
```

---

### 5. Starting Hadoop

#### 5.1: Format NameNode
```bash
hdfs namenode -format
```

#### 5.2: Start HDFS
```bash
start-dfs.sh
```

#### 5.3: Start YARN
```bash
start-yarn.sh
```

#### 5.4: Verify Services
```bash
jps
```

---

## Running the WordCount Project

### 1. Create a Maven Project
- Add the following dependencies in `pom.xml`:
```xml
<dependencies>
    <dependency>
        <groupId>org.apache.hadoop</groupId>
        <artifactId>hadoop-common</artifactId>
        <version>3.3.6</version>
    </dependency>
    <dependency>
        <groupId>org.apache.hadoop</groupId>
        <artifactId>hadoop-mapreduce-client-core</artifactId>
        <version>3.3.6</version>
    </dependency>
</dependencies>
```

### 2. Implement WordCount Classes
- **Mapper**: `WC_Mapper.java`
- **Reducer**: `WC_Reducer.java`
- **Runner**: `WC_Runner.java`

### 3. Build the Project
```bash
mvn clean package
```

### 4. Run the Project
#### Create Input File
```bash
nano input.txt
```

Add sample text:
```
This is the input file for hadoop project
This is for Cloud Computing with AKB hadoop project file
This is done for now
```

#### Upload to HDFS
```bash
hadoop fs -mkdir /input
hadoop fs -put input.txt /input
```

#### Execute WordCount Job
```bash
hadoop jar target/wordcount-1.0-SNAPSHOT.jar org.akb.WC_Runner /input /output
```

#### View Output
```bash
hadoop fs -cat /output/part-00000
```

---

## Conclusion

By following this guide, you can successfully set up Hadoop, create a WordCount project, and run it on a distributed environment. The WordCount example demonstrates the basics of Hadoop's MapReduce framework.
```

You can copy-paste this into your GitHub repository's README.md file!
