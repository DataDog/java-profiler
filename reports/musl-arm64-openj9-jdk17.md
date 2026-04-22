---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 14:08:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 9 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776881025 59
1776881030 59
1776881035 59
1776881040 59
1776881045 59
1776881050 59
1776881055 59
1776881060 59
1776881065 59
1776881071 59
1776881076 59
1776881081 59
1776881086 59
1776881091 59
1776881096 59
1776881101 59
1776881106 64
1776881111 64
1776881116 64
1776881121 64
```
</details>

---

