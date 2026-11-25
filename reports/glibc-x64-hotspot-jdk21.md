---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:52:57 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 59-81 cores)</summary>

```
1795614489 59
1795614494 59
1795614499 59
1795614504 59
1795614509 59
1795614514 59
1795614519 59
1795614524 79
1795614529 79
1795614534 79
1795614539 79
1795614544 81
1795614549 81
1795614554 81
1795614559 81
1795614564 79
1795614569 79
1795614574 79
1795614579 79
1795614584 79
```
</details>

---

