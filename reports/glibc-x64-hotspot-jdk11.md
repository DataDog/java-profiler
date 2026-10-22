---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 13:10:12 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 80-86 cores)</summary>

```
1792688651 84
1792688656 86
1792688661 86
1792688666 86
1792688671 80
1792688676 80
1792688681 80
1792688686 80
1792688691 82
1792688696 82
1792688701 82
1792688706 82
1792688711 82
1792688716 82
1792688721 82
1792688726 82
1792688731 82
1792688736 82
1792688741 82
1792688746 82
```
</details>

---

