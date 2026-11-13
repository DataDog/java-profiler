---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:44:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794584451 46
1794584456 46
1794584461 46
1794584466 46
1794584471 46
1794584476 46
1794584481 46
1794584486 46
1794584491 46
1794584496 46
1794584501 48
1794584506 48
1794584511 48
1794584516 48
1794584521 48
1794584526 48
1794584531 48
1794584536 48
1794584541 48
1794584546 48
```
</details>

---

