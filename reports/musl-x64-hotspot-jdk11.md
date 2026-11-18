---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:06:22 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 23-24 cores)</summary>

```
1795010486 24
1795010491 24
1795010496 24
1795010501 24
1795010506 24
1795010511 24
1795010516 24
1795010521 24
1795010526 24
1795010531 24
1795010536 24
1795010541 24
1795010546 24
1795010551 24
1795010556 24
1795010561 24
1795010566 24
1795010571 24
1795010576 24
1795010581 23
```
</details>

---

