#define trigPin 9
#define echoPin 8
#define ALERT 13   // Buzzer + Vibration Motor (shared output pin)

long distance;

// Function to get a stable distance reading using averaging
long readDistance()
{
  long sum = 0;

  for(int i = 0; i < 5; i++)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 20000); // Read echo time with timeout
    long d = duration / 58.2; // Convert time to distance in cm

    sum += d;
    delay(10); // Small delay between readings
  }

  return sum / 5; // Return average distance
}

void setup() 
{
  Serial.begin(9600);          // Initialize serial communication
  pinMode(trigPin, OUTPUT);    // Set trigger pin as output
  pinMode(echoPin, INPUT);     // Set echo pin as input
  pinMode(ALERT, OUTPUT);      // Set alert pin as output
}

void loop() 
{
  distance = readDistance();   // Get filtered distance value

  Serial.println(distance);    // Print distance for debugging

  // Ignore invalid readings
  if (distance <= 0 || distance > 200)
  {
    digitalWrite(ALERT, LOW);  // Ensure alert is off
    return;
  }

  // --- Alert system based on distance levels ---
  
  if (distance > 60)
  {
    digitalWrite(ALERT, LOW); // Safe zone (no alert)
  }

  else if (distance > 30)
  {
    alert(400); // Low alert (slow pattern)
  }

  else if (distance > 15)
  {
    alert(150); // Medium alert (faster pattern)
  }

  else
  {
    alert(50);  // High alert (very fast pattern)
  }
}

// Function to generate alert signal (sound + vibration)
void alert(int t)
{
  digitalWrite(ALERT, HIGH);
  delay(t);
  digitalWrite(ALERT, LOW);
  delay(t);
}