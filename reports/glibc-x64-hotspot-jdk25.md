---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-04 19:34:25 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 997 |
| Sample Rate | 16.62/sec |
| Health Score | 1039% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 56-60 cores)</summary>

```
1770251318 56
1770251323 56
1770251328 56
1770251333 56
1770251338 56
1770251343 56
1770251348 56
1770251353 56
1770251358 60
1770251363 60
1770251368 60
1770251373 60
1770251378 60
1770251383 60
1770251388 60
1770251393 60
1770251398 60
1770251403 60
1770251408 60
1770251413 60
```
</details>

---

