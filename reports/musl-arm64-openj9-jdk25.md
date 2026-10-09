---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 08:20:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 12 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 17-64 cores)</summary>

```
1791548000 17
1791548005 17
1791548010 17
1791548015 17
1791548020 17
1791548025 17
1791548030 17
1791548035 17
1791548040 64
1791548045 64
1791548050 64
1791548055 64
1791548060 64
1791548065 64
1791548070 64
1791548075 64
1791548080 64
1791548085 64
1791548090 64
1791548095 64
```
</details>

---

