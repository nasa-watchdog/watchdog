# Builds the action recognizer neural network
#
# University of California, Santa Barbara
# 2019

from keras.models import Sequential
from keras.models import Dense

model.add(Dense(units=64, activation='relu', input_dim=100))
model.add(Dropout(0.5))
model.add(Dense(units=10, activation='softmax'))
model.add(Dropout(0.5))

model.compile(loss='categorical_crossentropy',
              optimizer='sgd',
              metrics=['accuracy'])

model.fit(x_train, y_train, epochs=5, batch_size=32)

classes = model.predict(x_test, batch_size=128)




