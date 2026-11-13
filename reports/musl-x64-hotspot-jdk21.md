---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:44:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 64-68 cores)</summary>

```
1794587952 66
1794587957 68
1794587962 68
1794587967 68
1794587972 68
1794587977 68
1794587982 68
1794587987 68
1794587992 68
1794587997 68
1794588002 68
1794588007 68
1794588012 68
1794588017 68
1794588022 68
1794588027 64
1794588032 64
1794588037 64
1794588042 64
1794588047 64
```
</details>

---

