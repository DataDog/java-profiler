---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 09:12:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1792156044 43
1792156049 43
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
1792156129 43
1792156135 43
1792156140 43
```
</details>

---

