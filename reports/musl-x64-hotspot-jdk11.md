---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:29:12 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 52-78 cores)</summary>

```
1795627391 78
1795627396 78
1795627401 78
1795627406 78
1795627411 78
1795627416 78
1795627421 78
1795627426 78
1795627431 78
1795627436 78
1795627441 52
1795627446 52
1795627451 52
1795627456 52
1795627461 52
1795627466 52
1795627471 52
1795627476 52
1795627481 52
1795627486 52
```
</details>

---

