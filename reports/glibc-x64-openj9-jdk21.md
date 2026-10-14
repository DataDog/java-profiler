---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 12:30:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 22-25 cores)</summary>

```
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
1791995180 24
1791995185 24
1791995190 24
```
</details>

---

