---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 12:30:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 22-25 cores)</summary>

```
1791995080 25
1791995085 25
1791995090 25
1791995095 25
1791995100 25
1791995105 25
1791995110 25
1791995115 25
1791995120 25
1791995125 25
1791995130 25
1791995135 25
1791995140 25
1791995145 22
1791995150 22
1791995155 22
1791995160 22
1791995165 22
1791995170 22
1791995175 24
```
</details>

---

