---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-03 08:20:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 34-53 cores)</summary>

```
1770124557 34
1770124562 36
1770124567 36
1770124572 36
1770124577 36
1770124582 39
1770124587 39
1770124592 39
1770124597 39
1770124602 39
1770124607 39
1770124612 39
1770124617 39
1770124622 39
1770124627 39
1770124632 39
1770124637 39
1770124642 39
1770124647 39
1770124652 53
```
</details>

---

