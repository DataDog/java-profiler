---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 07:26:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 12 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1792408927 58
1792408932 58
1792408937 58
1792408942 58
1792408947 58
1792408952 58
1792408957 58
1792408962 58
1792408967 58
1792408972 56
1792408977 56
1792408982 56
1792408987 56
1792408992 56
1792408997 56
1792409002 56
1792409007 56
1792409013 56
1792409018 56
1792409023 56
```
</details>

---

