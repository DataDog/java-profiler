---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:05:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1795608044 45
1795608049 45
1795608054 45
1795608059 45
1795608064 40
1795608069 40
1795608074 40
1795608079 40
1795608084 40
1795608089 40
1795608094 40
1795608099 40
1795608104 40
1795608109 40
1795608114 43
1795608119 43
1795608124 43
1795608129 43
1795608134 43
1795608139 43
```
</details>

---

