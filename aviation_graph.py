import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("/Users/jose/CLionProjects/RadarTech/cmake-build-debug/PID_F35_DATA.csv")

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))

ax1.plot(df["Cycle"], df["Altitude"], label="Altitude")
ax1.axhline(y=30000, color='r', linestyle='--', label="Target")
ax1.set_xlabel("Clock Cycle")
ax1.set_ylabel("Altitude (ft)")
ax1.set_title("F-35 PID Altitude Control")
ax1.legend()
ax1.grid(True)

ax2.plot(df["Cycle"], df["Error"], color='orange', label="Error")
ax2.axhline(y=0, color='r', linestyle='--')
ax2.set_xlabel("Clock Cycle")
ax2.set_ylabel("Error (ft)")
ax2.set_title("Tracking Error Over Time")
ax2.legend()
ax2.grid(True)

plt.tight_layout()
plt.show()