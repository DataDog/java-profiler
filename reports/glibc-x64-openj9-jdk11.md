---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:13:48 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 68-89 cores)</summary>

```
1793614125 72
1793614130 70
1793614135 70
1793614140 73
1793614145 73
1793614150 68
1793614155 68
1793614160 68
1793614165 68
1793614170 68
1793614175 68
1793614180 68
1793614185 68
1793614190 68
1793614195 68
1793614200 68
1793614205 68
1793614210 68
1793614215 68
1793614220 68
```
</details>

---

