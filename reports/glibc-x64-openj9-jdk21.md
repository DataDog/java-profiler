---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 09:25:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 68-81 cores)</summary>

```
1777555325 81
1777555331 81
1777555336 81
1777555341 81
1777555346 81
1777555351 81
1777555356 81
1777555361 81
1777555366 81
1777555371 77
1777555376 77
1777555381 81
1777555386 81
1777555391 81
1777555396 76
1777555401 76
1777555406 72
1777555411 72
1777555416 72
1777555421 72
```
</details>

---

