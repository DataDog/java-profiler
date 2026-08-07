---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-07 07:56:32 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 74-81 cores)</summary>

```
1786103546 81
1786103551 81
1786103556 81
1786103561 81
1786103566 81
1786103571 81
1786103576 78
1786103581 78
1786103586 78
1786103591 78
1786103596 78
1786103601 78
1786103606 76
1786103611 76
1786103616 76
1786103621 76
1786103626 76
1786103631 76
1786103636 76
1786103641 76
```
</details>

---

