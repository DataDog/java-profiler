---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:52:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 868 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 12 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (5 unique values: 51-61 cores)</summary>

```
1789731973 53
1789731978 53
1789731983 53
1789731988 51
1789731993 51
1789731998 53
1789732003 53
1789732008 53
1789732013 53
1789732018 53
1789732023 53
1789732028 53
1789732033 53
1789732038 53
1789732043 55
1789732048 55
1789732053 54
1789732058 54
1789732063 54
1789732068 54
```
</details>

---

