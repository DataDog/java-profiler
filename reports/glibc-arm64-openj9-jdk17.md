---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:22:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1795429047 44
1795429052 44
1795429057 39
1795429062 39
1795429067 39
1795429072 39
1795429077 39
1795429082 39
1795429087 39
1795429092 39
1795429097 39
1795429102 39
1795429107 39
1795429112 39
1795429117 39
1795429122 39
1795429127 39
1795429132 39
1795429137 39
1795429142 39
```
</details>

---

