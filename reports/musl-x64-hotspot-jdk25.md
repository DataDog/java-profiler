---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-01 12:28:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 36-44 cores)</summary>

```
1788279636 44
1788279641 44
1788279646 44
1788279651 44
1788279656 36
1788279661 36
1788279666 36
1788279671 39
1788279676 39
1788279681 39
1788279686 39
1788279691 39
1788279696 39
1788279701 39
1788279706 39
1788279711 39
1788279716 39
1788279721 39
1788279726 39
1788279731 37
```
</details>

---

