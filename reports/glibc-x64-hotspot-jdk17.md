---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 08:32:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 55-79 cores)</summary>

```
1795181278 55
1795181283 55
1795181288 55
1795181293 55
1795181298 55
1795181303 57
1795181308 57
1795181313 57
1795181318 57
1795181323 57
1795181328 57
1795181333 57
1795181338 57
1795181343 57
1795181348 57
1795181353 79
1795181358 79
1795181363 79
1795181368 79
1795181373 79
```
</details>

---

