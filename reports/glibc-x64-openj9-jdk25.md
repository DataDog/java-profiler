---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:22:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 11 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1020 |
| Sample Rate | 17.00/sec |
| Health Score | 1062% |
| Threads | 13 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1770826265 66
1770826270 64
1770826275 64
1770826280 64
1770826285 64
1770826290 64
1770826295 64
1770826300 64
1770826305 64
1770826310 64
1770826315 64
1770826320 64
1770826325 64
1770826330 64
1770826335 64
1770826340 64
1770826345 64
1770826350 64
1770826355 64
1770826360 62
```
</details>

---

