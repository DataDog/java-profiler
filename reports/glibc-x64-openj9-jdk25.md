---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:44:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795614060 96
1795614065 96
1795614070 96
1795614075 94
1795614080 94
1795614085 94
1795614090 94
1795614095 94
1795614100 94
1795614105 96
1795614110 96
1795614115 96
1795614120 96
1795614125 96
1795614130 96
1795614135 96
1795614140 96
1795614145 96
1795614150 96
1795614155 96
```
</details>

---

