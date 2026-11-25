---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:23:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 12 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795605479 64
1795605484 64
1795605489 64
1795605494 64
1795605499 64
1795605504 64
1795605509 64
1795605514 64
1795605519 60
1795605524 60
1795605529 60
1795605534 60
1795605539 60
1795605544 60
1795605549 60
1795605554 60
1795605559 60
1795605564 60
1795605569 60
1795605574 60
```
</details>

---

