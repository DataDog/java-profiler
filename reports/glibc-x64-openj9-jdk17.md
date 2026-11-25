---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:29:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 71-87 cores)</summary>

```
1795627401 71
1795627406 71
1795627411 71
1795627416 71
1795627421 71
1795627426 71
1795627431 71
1795627436 71
1795627441 71
1795627446 85
1795627451 85
1795627456 85
1795627461 85
1795627466 85
1795627471 85
1795627476 85
1795627481 85
1795627486 85
1795627491 85
1795627496 85
```
</details>

---

