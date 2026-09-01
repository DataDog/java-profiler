---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:03:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 60-80 cores)</summary>

```
1788289019 80
1788289024 80
1788289029 80
1788289034 74
1788289039 74
1788289044 74
1788289049 74
1788289054 74
1788289059 74
1788289064 68
1788289069 68
1788289074 60
1788289079 60
1788289084 68
1788289089 68
1788289094 68
1788289099 68
1788289104 68
1788289109 68
1788289114 66
```
</details>

---

