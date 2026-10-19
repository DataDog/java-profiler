---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 06:50:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792406785 32
1792406790 32
1792406795 32
1792406800 32
1792406805 32
1792406811 32
1792406816 32
1792406821 32
1792406826 32
1792406831 32
1792406836 32
1792406841 32
1792406846 32
1792406851 32
1792406856 32
1792406861 32
1792406866 32
1792406871 32
1792406876 32
1792406881 32
```
</details>

---

