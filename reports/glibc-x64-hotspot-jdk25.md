---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:55:42 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 13 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1770137451 96
1770137456 96
1770137461 96
1770137466 96
1770137471 96
1770137476 96
1770137481 96
1770137486 86
1770137491 86
1770137496 86
1770137501 86
1770137506 86
1770137511 86
1770137516 86
1770137521 86
1770137526 86
1770137531 86
1770137536 86
1770137541 86
1770137546 86
```
</details>

---

