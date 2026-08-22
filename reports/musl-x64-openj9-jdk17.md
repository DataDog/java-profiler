---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 08:14:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1787400587 81
1787400592 81
1787400597 81
1787400602 81
1787400607 81
1787400612 81
1787400617 81
1787400622 79
1787400627 79
1787400632 79
1787400637 79
1787400642 79
1787400647 79
1787400652 79
1787400657 79
1787400662 79
1787400667 79
1787400672 81
1787400677 81
1787400682 81
```
</details>

---

