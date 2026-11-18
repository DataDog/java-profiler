---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (6 unique values: 53-64 cores)</summary>

```
1795010476 62
1795010481 62
1795010486 59
1795010491 59
1795010496 59
1795010501 59
1795010506 59
1795010511 64
1795010516 64
1795010521 56
1795010526 56
1795010531 57
1795010536 57
1795010541 57
1795010546 57
1795010551 57
1795010556 57
1795010561 57
1795010566 59
1795010571 59
```
</details>

---

