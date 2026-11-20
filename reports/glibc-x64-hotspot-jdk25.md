---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 08:32:50 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 74-83 cores)</summary>

```
1795181308 74
1795181313 74
1795181318 74
1795181323 74
1795181328 74
1795181333 74
1795181338 74
1795181343 74
1795181348 83
1795181353 83
1795181358 81
1795181363 81
1795181368 81
1795181373 81
1795181378 81
1795181383 79
1795181388 79
1795181393 79
1795181398 79
1795181403 77
```
</details>

---

