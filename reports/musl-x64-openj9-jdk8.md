---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-07 12:24:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 6-12 cores)</summary>

```
1786119559 6
1786119564 6
1786119569 6
1786119574 6
1786119579 6
1786119584 6
1786119589 6
1786119594 6
1786119599 6
1786119604 6
1786119609 6
1786119614 6
1786119619 6
1786119624 6
1786119629 6
1786119634 8
1786119639 8
1786119644 12
1786119649 12
1786119654 12
```
</details>

---

