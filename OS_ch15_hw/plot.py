import matplotlib.pyplot as plt

# Your data values
limits = [0, 128, 256, 512, 1024]
fractions = [0.0, 0.2, 0.2, 0.5, 1.0]

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(limits, fractions, marker='o', linestyle='-', color='b')

# Labeling the plot
plt.title("Fraction of Valid Addresses vs. Limit Register")
plt.xlabel("Limit (Bytes)")
plt.ylabel("Fraction of Valid Addresses")
plt.grid(True)
plt.tight_layout()

# Show the plot
plt.show()
