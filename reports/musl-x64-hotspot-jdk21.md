---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 08:47:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 71-81 cores)</summary>

```
1794922812 81
1794922817 81
1794922822 81
1794922827 81
1794922832 81
1794922837 81
1794922842 81
1794922847 81
1794922852 81
1794922857 81
1794922862 79
1794922867 79
1794922872 79
1794922877 79
1794922882 79
1794922887 79
1794922892 79
1794922897 79
1794922902 79
1794922907 77
```
</details>

---

