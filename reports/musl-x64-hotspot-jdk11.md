---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 17:34:39 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 84-92 cores)</summary>

```
1778189409 84
1778189414 84
1778189419 84
1778189424 84
1778189429 84
1778189434 89
1778189439 89
1778189444 89
1778189449 89
1778189454 89
1778189459 89
1778189464 89
1778189469 89
1778189474 92
1778189479 92
1778189484 92
1778189489 92
1778189494 92
1778189499 92
1778189504 92
```
</details>

---

