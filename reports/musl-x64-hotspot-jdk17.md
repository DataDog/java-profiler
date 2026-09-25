---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 09:02:26 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (5 unique values: 53-84 cores)</summary>

```
1790341015 53
1790341020 53
1790341025 55
1790341030 55
1790341035 55
1790341040 64
1790341045 64
1790341050 64
1790341055 64
1790341060 64
1790341065 62
1790341070 62
1790341075 62
1790341080 62
1790341085 62
1790341090 62
1790341095 62
1790341100 62
1790341105 62
1790341110 62
```
</details>

---

