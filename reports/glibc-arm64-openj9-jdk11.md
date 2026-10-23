---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1039 |
| Sample Rate | 17.32/sec |
| Health Score | 1082% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792767115 48
1792767120 48
1792767125 48
1792767130 48
1792767135 48
1792767140 48
1792767145 43
1792767150 43
1792767155 43
1792767160 43
1792767165 43
1792767170 43
1792767175 43
1792767180 43
1792767185 43
1792767190 43
1792767195 43
1792767200 43
1792767205 43
1792767210 43
```
</details>

---

