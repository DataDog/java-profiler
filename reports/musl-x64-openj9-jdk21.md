---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-16 11:32:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1776352957 32
1776352962 32
1776352967 32
1776352972 32
1776352977 32
1776352982 32
1776352987 32
1776352992 32
1776352997 32
1776353002 32
1776353007 32
1776353012 32
1776353017 32
1776353022 32
1776353027 32
1776353032 32
1776353037 32
1776353042 32
1776353047 30
1776353052 30
```
</details>

---

