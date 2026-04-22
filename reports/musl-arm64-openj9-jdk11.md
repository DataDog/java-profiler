---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 13:39:01 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 7 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776879060 64
1776879065 64
1776879070 64
1776879075 64
1776879080 64
1776879085 64
1776879090 64
1776879095 64
1776879100 64
1776879105 64
1776879110 64
1776879115 64
1776879120 64
1776879125 64
1776879130 64
1776879135 64
1776879140 64
1776879145 64
1776879150 64
1776879155 64
```
</details>

---

