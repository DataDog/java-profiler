---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 06:24:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793704787 64
1793704792 64
1793704797 64
1793704802 64
1793704807 64
1793704812 64
1793704817 64
1793704822 64
1793704827 64
1793704832 64
1793704837 64
1793704842 64
1793704847 64
1793704852 64
1793704857 64
1793704862 64
1793704867 64
1793704872 64
1793704877 64
1793704882 64
```
</details>

---

