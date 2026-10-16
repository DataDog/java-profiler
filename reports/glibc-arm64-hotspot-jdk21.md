---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 09:11:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 9 |
| Allocations | 64 |

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
<summary>CPU Timeline (3 unique values: 30-43 cores)</summary>

```
1792156054 43
1792156059 43
1792156064 43
1792156069 43
1792156074 43
1792156079 43
1792156084 43
1792156089 43
1792156094 43
1792156099 43
1792156104 43
1792156109 43
1792156114 43
1792156119 43
1792156124 43
1792156129 38
1792156134 38
1792156139 30
1792156144 30
1792156149 30
```
</details>

---

