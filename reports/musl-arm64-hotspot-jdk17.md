---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:23:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 10-14 cores)</summary>

```
1795605434 14
1795605439 14
1795605444 14
1795605449 14
1795605454 14
1795605459 14
1795605464 14
1795605469 14
1795605474 14
1795605479 14
1795605484 14
1795605489 14
1795605494 14
1795605499 14
1795605504 14
1795605509 14
1795605514 14
1795605519 10
1795605524 10
1795605529 10
```
</details>

---

