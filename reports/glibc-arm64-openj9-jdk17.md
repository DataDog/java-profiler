---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 16:22:25 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (3 unique values: 28-35 cores)</summary>

```
1794259063 30
1794259068 35
1794259073 35
1794259078 28
1794259083 28
1794259088 28
1794259093 28
1794259098 28
1794259104 28
1794259109 28
1794259114 28
1794259119 28
1794259124 28
1794259129 28
1794259134 28
1794259139 28
1794259144 28
1794259149 28
1794259154 28
1794259159 28
```
</details>

---

