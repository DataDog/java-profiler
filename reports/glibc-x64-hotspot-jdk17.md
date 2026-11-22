---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 17:04:20 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 31-65 cores)</summary>

```
1795384572 48
1795384577 48
1795384582 48
1795384587 48
1795384592 48
1795384597 57
1795384602 57
1795384607 57
1795384612 57
1795384617 57
1795384622 57
1795384627 65
1795384632 65
1795384637 65
1795384642 48
1795384647 48
1795384652 48
1795384657 48
1795384662 48
1795384667 48
```
</details>

---

