---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 05:45:51 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1786527641 29
1786527646 29
1786527651 29
1786527656 31
1786527661 31
1786527666 31
1786527671 31
1786527676 31
1786527681 31
1786527686 31
1786527691 31
1786527696 31
1786527701 31
1786527706 31
1786527711 31
1786527716 31
1786527721 31
1786527726 31
1786527731 31
1786527736 31
```
</details>

---

