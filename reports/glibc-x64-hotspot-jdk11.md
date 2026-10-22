---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 05:55:17 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1792662701 81
1792662706 81
1792662711 81
1792662716 81
1792662721 81
1792662726 81
1792662731 83
1792662736 83
1792662741 83
1792662746 83
1792662751 83
1792662756 83
1792662761 83
1792662766 83
1792662771 83
1792662776 83
1792662781 81
1792662786 81
1792662791 81
1792662796 81
```
</details>

---

