---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 05:17:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (6 unique values: 50-62 cores)</summary>

```
1792141922 61
1792141927 61
1792141932 62
1792141937 62
1792141942 62
1792141947 62
1792141952 62
1792141957 62
1792141962 62
1792141967 62
1792141972 62
1792141977 60
1792141982 60
1792141987 60
1792141992 60
1792141997 55
1792142002 55
1792142007 55
1792142013 55
1792142018 55
```
</details>

---

