---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-29 11:09:02 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 969 |
| Sample Rate | 16.15/sec |
| Health Score | 1009% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 59-67 cores)</summary>

```
1777475043 61
1777475048 59
1777475053 59
1777475058 59
1777475063 62
1777475068 62
1777475073 62
1777475078 62
1777475083 62
1777475088 62
1777475093 62
1777475098 62
1777475103 62
1777475108 62
1777475113 62
1777475118 62
1777475123 62
1777475128 62
1777475133 62
1777475138 67
```
</details>

---

