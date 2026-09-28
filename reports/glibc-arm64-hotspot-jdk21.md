---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 08:01:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 9 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (4 unique values: 41-46 cores)</summary>

```
1790596567 44
1790596572 46
1790596577 46
1790596582 46
1790596587 46
1790596592 46
1790596597 46
1790596602 46
1790596607 46
1790596612 41
1790596617 41
1790596622 41
1790596627 41
1790596632 41
1790596637 41
1790596642 41
1790596647 41
1790596652 43
1790596657 43
1790596662 43
```
</details>

---

