
  ## WeatherAUS_Predict.R ##

# This script will use a binary classification model
# to predict whether or not it will rain in Australia
# tomorrow

library(dplyr)

  ## Data Preprocessing ##

# Read in the data
data <- read.csv("./WeatherAUS/WeatherAUS.csv")

# Display the head of the data
head(data)

# Exclude data in which the dependent variable RainTomorrow is NA
data <- na.omit(data)

# Convert the 'Yes' and 'No' in RainTomorrow to 1 and 0
data$RainTomorrow <- if_else(data$RainTomorrow == "Yes", 1, 0)

  ## Data Partitioning ##

# Partitions a dataset into two segments based on partition
# data = the data to be passed into the function
# partition = float from 0 to 1, determines the size of the partition
# seed = the random seed which determines which indecies are partitioned
# Returns a vector containing the smaller and larger partitions
createTrainingPartition <- function(data, partition, seed)
{
  # Get the sample size from partition
  smp_size <- floor(partition * nrow(data))
  
  # The seed makes the partition reproducible
  set.seed(seed)
  
  # Get the training indecies
  train_ind <- sample(seq_len(nrow(data)), size = smp_size)
  
  # Split the data accordingly
  train <- data[train_ind, ]
  test <- data[-train_ind, ]
  
  return(list("train" = train, "test" = test))
}

# Create the partitions
partition <- createTrainingPartition(data, 0.9, 1234)

# Assign the training partition
train <- partition["train"]$train

# Assign the testing partition
test <- partition["test"]$test
