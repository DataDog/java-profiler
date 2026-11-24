---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 11:42:49 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (6 unique values: 68-79 cores)</summary>

```
1795538297 79
1795538302 79
1795538307 79
1795538312 79
1795538317 79
1795538322 79
1795538327 79
1795538332 79
1795538337 79
1795538342 79
1795538347 79
1795538352 77
1795538357 77
1795538362 77
1795538367 70
1795538372 70
1795538377 70
1795538382 72
1795538387 72
1795538392 74
```
</details>

---

