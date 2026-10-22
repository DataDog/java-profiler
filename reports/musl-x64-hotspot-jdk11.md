---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:39:26 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792686870 46
1792686875 46
1792686880 46
1792686885 46
1792686890 46
1792686895 46
1792686900 46
1792686905 46
1792686910 46
1792686915 48
1792686920 48
1792686925 48
1792686930 48
1792686935 48
1792686940 48
1792686945 48
1792686950 48
1792686955 46
1792686960 46
1792686965 46
```
</details>

---

