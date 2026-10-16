---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 09:12:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792156014 38
1792156019 38
1792156024 38
1792156029 38
1792156034 38
1792156039 38
1792156044 43
1792156049 43
1792156054 43
1792156059 43
1792156064 43
1792156069 43
1792156074 43
1792156079 48
1792156084 48
1792156089 48
1792156094 48
1792156099 43
1792156104 43
1792156109 43
```
</details>

---

