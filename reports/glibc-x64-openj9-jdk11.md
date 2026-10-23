---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 8 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1792767115 88
1792767120 88
1792767125 88
1792767130 88
1792767135 88
1792767140 88
1792767145 88
1792767150 88
1792767155 88
1792767160 88
1792767165 88
1792767170 88
1792767175 88
1792767180 88
1792767185 88
1792767190 96
1792767195 96
1792767200 96
1792767205 96
1792767210 96
```
</details>

---

