---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-10 13:55:48 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1773164995 58
1773165000 58
1773165005 58
1773165010 58
1773165015 58
1773165020 56
1773165025 56
1773165030 56
1773165035 56
1773165040 58
1773165045 58
1773165050 58
1773165055 58
1773165060 58
1773165065 58
1773165070 58
1773165075 58
1773165080 58
1773165085 58
1773165090 58
```
</details>

---

