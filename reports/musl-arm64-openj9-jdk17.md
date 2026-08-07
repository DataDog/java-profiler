---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 07:56:31 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (3 unique values: 44-56 cores)</summary>

```
1786103486 56
1786103491 51
1786103496 51
1786103501 51
1786103506 51
1786103511 51
1786103516 51
1786103521 51
1786103526 51
1786103531 51
1786103536 56
1786103541 56
1786103546 56
1786103551 56
1786103556 56
1786103561 56
1786103566 56
1786103571 56
1786103576 56
1786103581 56
```
</details>

---

