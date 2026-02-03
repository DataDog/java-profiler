---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:55:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1107 |
| Sample Rate | 18.45/sec |
| Health Score | 1153% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1770137439 29
1770137444 29
1770137449 29
1770137454 29
1770137459 29
1770137464 29
1770137469 29
1770137474 32
1770137479 32
1770137484 32
1770137489 32
1770137494 32
1770137499 32
1770137504 32
1770137509 32
1770137514 32
1770137519 32
1770137524 32
1770137529 32
1770137534 32
```
</details>

---

