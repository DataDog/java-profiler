---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 08:03:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (4 unique values: 73-89 cores)</summary>

```
1789991892 89
1789991897 89
1789991902 89
1789991907 81
1789991912 81
1789991917 81
1789991922 81
1789991927 81
1789991932 81
1789991937 81
1789991942 81
1789991947 81
1789991952 81
1789991957 81
1789991962 81
1789991967 81
1789991972 81
1789991977 81
1789991982 81
1789991987 83
```
</details>

---

