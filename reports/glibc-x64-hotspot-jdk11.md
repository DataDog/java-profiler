---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:40:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1795192429 64
1795192434 64
1795192439 64
1795192444 64
1795192449 64
1795192454 64
1795192459 66
1795192464 66
1795192469 66
1795192474 66
1795192479 64
1795192484 64
1795192489 64
1795192494 64
1795192499 64
1795192504 64
1795192509 64
1795192514 64
1795192519 64
1795192524 64
```
</details>

---

