---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:45:16 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 32-53 cores)</summary>

```
1777394307 32
1777394312 32
1777394317 32
1777394322 32
1777394327 32
1777394332 32
1777394337 32
1777394342 32
1777394347 51
1777394352 51
1777394357 51
1777394362 51
1777394367 51
1777394372 51
1777394377 51
1777394382 51
1777394387 51
1777394392 51
1777394397 51
1777394402 51
```
</details>

---

