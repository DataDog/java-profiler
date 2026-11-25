---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:28:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 60-62 cores)</summary>

```
1795627371 60
1795627376 60
1795627381 60
1795627386 60
1795627391 60
1795627396 60
1795627401 60
1795627406 60
1795627411 60
1795627416 60
1795627421 62
1795627426 62
1795627431 62
1795627436 62
1795627441 62
1795627446 62
1795627451 62
1795627456 61
1795627461 61
1795627466 61
```
</details>

---

