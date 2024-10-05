import random

# Number of alloys
num_alloys = 10000000
alloys_data = []

# Create a sample of alloys with IDs and random flexibility and conductivity values
for i in range(num_alloys):
    # Generate a unique ID for each alloy
    alloy_id = f"Alloy_{i+1}"
    
    # Randomly generate flexibility and conductivity values
    flexibility = round(random.uniform(1.0, 10.0), 1)  # Flexibility between 1.0 and 10.0
    conductivity = round(random.uniform(1.0, 10.0), 1)  # Conductivity between 1.0 and 10.0
    
    # Append the generated alloy data to the list
    alloys_data.append(f"{alloy_id} {flexibility} {conductivity}")

# Combine all lines into a single list
output_data = [f"{num_alloys}"] + alloys_data

# Write to a file "input_sample_"
with open('input_sample_7', 'w') as file:
    file.write('\n'.join(output_data))
