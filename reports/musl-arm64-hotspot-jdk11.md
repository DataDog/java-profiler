---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:33:04 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 11 |
| Allocations | 160 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789719954 25
1789719959 25
1789719964 25
1789719969 25
1789719974 25
1789719979 25
1789719984 25
1789719989 25
1789719994 25
1789719999 25
1789720004 25
1789720009 25
1789720014 25
1789720019 25
1789720024 25
1789720029 25
1789720034 25
1789720039 25
1789720044 25
1789720049 25
```
</details>

---

