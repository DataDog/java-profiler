---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-22 17:04:22 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 31-65 cores)</summary>

```
1795384570 48
1795384575 48
1795384580 48
1795384585 48
1795384590 48
1795384595 48
1795384600 57
1795384605 57
1795384610 57
1795384615 57
1795384620 57
1795384625 57
1795384630 65
1795384635 65
1795384640 48
1795384645 48
1795384650 48
1795384655 48
1795384660 48
1795384665 48
```
</details>

---

