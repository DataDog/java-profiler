---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 18:13:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 12 |
| Allocations | 199 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777414004 64
1777414009 64
1777414014 64
1777414019 64
1777414024 64
1777414029 64
1777414034 64
1777414039 64
1777414044 64
1777414049 64
1777414054 64
1777414059 64
1777414064 64
1777414069 64
1777414074 64
1777414079 64
1777414084 64
1777414089 64
1777414094 64
1777414099 59
```
</details>

---

