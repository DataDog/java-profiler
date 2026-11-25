---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:52:58 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 32-69 cores)</summary>

```
1795614524 34
1795614529 34
1795614534 32
1795614539 32
1795614544 32
1795614549 32
1795614554 32
1795614559 32
1795614564 32
1795614569 32
1795614574 32
1795614579 32
1795614584 32
1795614589 32
1795614594 32
1795614599 32
1795614604 41
1795614609 41
1795614614 41
1795614619 41
```
</details>

---

