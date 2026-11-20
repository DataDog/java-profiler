---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:37:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 10 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795195957 50
1795195962 50
1795195967 50
1795195972 50
1795195977 50
1795195982 50
1795195987 50
1795195992 50
1795195997 50
1795196002 50
1795196007 50
1795196012 50
1795196017 50
1795196022 50
1795196027 50
1795196032 50
1795196037 50
1795196042 50
1795196047 50
1795196052 50
```
</details>

---

