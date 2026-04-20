---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 11:41:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 11 |
| Allocations | 109 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 13 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776699084 64
1776699089 64
1776699094 64
1776699099 64
1776699104 59
1776699109 59
1776699114 59
1776699119 59
1776699124 59
1776699129 59
1776699134 59
1776699139 59
1776699144 59
1776699149 59
1776699154 59
1776699159 59
1776699164 59
1776699169 59
1776699174 59
1776699179 59
```
</details>

---

