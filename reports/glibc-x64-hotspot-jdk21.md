---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:43:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (5 unique values: 48-84 cores)</summary>

```
1789979996 84
1789980001 84
1789980006 84
1789980011 56
1789980016 56
1789980021 56
1789980026 56
1789980031 56
1789980036 66
1789980041 66
1789980046 66
1789980051 66
1789980056 66
1789980061 66
1789980066 68
1789980071 68
1789980076 68
1789980081 68
1789980086 48
1789980091 48
```
</details>

---

