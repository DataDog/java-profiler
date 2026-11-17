---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:43:09 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 6 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 15 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794915518 38
1794915523 38
1794915528 38
1794915533 38
1794915538 38
1794915543 38
1794915548 38
1794915553 38
1794915558 38
1794915563 38
1794915569 51
1794915574 51
1794915579 51
1794915584 51
1794915589 51
1794915594 51
1794915599 51
1794915604 51
1794915609 51
1794915614 51
```
</details>

---

