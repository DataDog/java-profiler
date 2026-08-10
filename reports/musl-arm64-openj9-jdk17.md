---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 08:31:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 29-35 cores)</summary>

```
1786364660 29
1786364665 29
1786364670 29
1786364675 29
1786364680 29
1786364685 32
1786364690 32
1786364695 32
1786364700 32
1786364705 32
1786364710 32
1786364715 32
1786364720 32
1786364725 35
1786364730 35
1786364735 35
1786364740 35
1786364745 35
1786364750 35
1786364755 35
```
</details>

---

