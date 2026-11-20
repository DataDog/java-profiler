---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 14:01:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795201040 50
1795201045 50
1795201050 50
1795201055 50
1795201060 50
1795201065 50
1795201070 50
1795201075 50
1795201080 50
1795201085 50
1795201090 50
1795201095 50
1795201100 50
1795201105 50
1795201110 50
1795201115 50
1795201120 50
1795201125 50
1795201130 50
1795201135 50
```
</details>

---

