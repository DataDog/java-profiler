---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:49:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (5 unique values: 50-79 cores)</summary>

```
1795621543 59
1795621548 59
1795621553 59
1795621559 59
1795621564 59
1795621569 59
1795621574 59
1795621579 59
1795621584 51
1795621589 51
1795621594 51
1795621599 79
1795621604 79
1795621609 79
1795621614 79
1795621619 53
1795621624 53
1795621629 50
1795621634 50
1795621639 50
```
</details>

---

