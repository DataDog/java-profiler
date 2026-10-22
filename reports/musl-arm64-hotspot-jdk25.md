---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 12:40:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1792686855 30
1792686860 30
1792686865 30
1792686870 30
1792686875 30
1792686880 30
1792686885 35
1792686890 35
1792686895 35
1792686900 35
1792686905 35
1792686910 35
1792686915 35
1792686920 35
1792686925 35
1792686930 35
1792686935 35
1792686940 35
1792686945 35
1792686950 35
```
</details>

---

