---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:59:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 10 |
| Allocations | 111 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786020956 48
1786020961 48
1786020966 48
1786020971 53
1786020976 53
1786020981 53
1786020986 53
1786020991 53
1786020996 53
1786021001 53
1786021006 53
1786021011 53
1786021016 53
1786021021 53
1786021026 53
1786021031 53
1786021036 53
1786021041 53
1786021046 53
1786021051 53
```
</details>

---

