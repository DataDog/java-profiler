---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-19 05:47:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 435 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 9 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1789811016 34
1789811021 34
1789811026 34
1789811031 34
1789811036 34
1789811041 34
1789811046 34
1789811051 34
1789811056 29
1789811061 29
1789811066 29
1789811071 24
1789811076 24
1789811081 24
1789811086 24
1789811091 24
1789811096 24
1789811101 24
1789811106 24
1789811111 24
```
</details>

---

