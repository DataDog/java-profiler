---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 11:41:36 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776699079 64
1776699084 64
1776699089 64
1776699094 64
1776699099 64
1776699104 64
1776699109 64
1776699114 64
1776699119 64
1776699124 64
1776699129 64
1776699134 64
1776699139 64
1776699144 64
1776699149 64
1776699154 64
1776699159 64
1776699164 64
1776699169 64
1776699174 59
```
</details>

---

