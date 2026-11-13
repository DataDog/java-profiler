---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:44:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1794587971 51
1794587976 51
1794587981 51
1794587987 51
1794587992 51
1794587997 51
1794588002 51
1794588007 51
1794588012 51
1794588017 51
1794588022 51
1794588027 51
1794588032 51
1794588037 51
1794588042 51
1794588047 51
1794588052 51
1794588057 51
1794588062 46
1794588067 46
```
</details>

---

