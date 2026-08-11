---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 04:47:01 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 34-48 cores)</summary>

```
1786437827 48
1786437832 48
1786437837 48
1786437842 48
1786437847 48
1786437852 48
1786437857 48
1786437862 48
1786437867 48
1786437872 48
1786437877 36
1786437882 36
1786437887 36
1786437892 36
1786437897 36
1786437902 36
1786437907 36
1786437912 36
1786437917 36
1786437922 36
```
</details>

---

