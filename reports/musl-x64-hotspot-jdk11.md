---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 06:24:52 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 24-52 cores)</summary>

```
1795778390 24
1795778395 24
1795778400 24
1795778405 24
1795778410 24
1795778415 24
1795778420 26
1795778425 26
1795778430 26
1795778435 26
1795778440 26
1795778445 26
1795778450 26
1795778455 26
1795778460 26
1795778465 26
1795778470 52
1795778475 52
1795778480 52
1795778485 52
```
</details>

---

