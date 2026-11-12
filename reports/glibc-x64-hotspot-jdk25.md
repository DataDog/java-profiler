---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:09:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 77-82 cores)</summary>

```
1794495925 77
1794495930 77
1794495935 77
1794495940 77
1794495945 77
1794495950 77
1794495955 77
1794495960 77
1794495965 82
1794495970 82
1794495975 82
1794495980 82
1794495985 82
1794495990 82
1794495995 82
1794496000 82
1794496005 82
1794496010 82
1794496015 82
1794496020 82
```
</details>

---

