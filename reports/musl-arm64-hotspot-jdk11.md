---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-19 05:47:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 10 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789810996 38
1789811001 38
1789811006 38
1789811011 38
1789811016 43
1789811021 43
1789811026 43
1789811031 43
1789811036 43
1789811041 43
1789811046 43
1789811051 43
1789811056 43
1789811061 43
1789811066 43
1789811071 43
1789811076 43
1789811081 43
1789811086 43
1789811091 43
```
</details>

---

