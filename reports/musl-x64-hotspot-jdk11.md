---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:49:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 9 |
| Allocations | 558 |

<details>
<summary>CPU Timeline (3 unique values: 58-73 cores)</summary>

```
1790765046 58
1790765051 58
1790765056 58
1790765061 58
1790765066 62
1790765071 62
1790765076 62
1790765081 62
1790765086 62
1790765091 62
1790765096 62
1790765101 62
1790765106 62
1790765111 62
1790765116 62
1790765121 62
1790765126 62
1790765131 62
1790765136 73
1790765141 73
```
</details>

---

