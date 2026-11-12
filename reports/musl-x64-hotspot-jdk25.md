---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:09:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 86-94 cores)</summary>

```
1794495915 86
1794495920 86
1794495925 86
1794495930 86
1794495935 94
1794495940 94
1794495945 94
1794495950 94
1794495955 94
1794495960 94
1794495965 94
1794495970 94
1794495975 94
1794495980 94
1794495985 94
1794495990 94
1794495995 94
1794496000 94
1794496005 94
1794496011 94
```
</details>

---

