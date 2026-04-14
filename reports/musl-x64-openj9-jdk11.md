---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-14 18:05:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 884 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 86-91 cores)</summary>

```
1776204080 91
1776204085 91
1776204090 91
1776204095 91
1776204100 91
1776204105 91
1776204110 86
1776204115 86
1776204120 86
1776204125 86
1776204130 86
1776204135 86
1776204140 86
1776204145 86
1776204150 86
1776204155 86
1776204160 86
1776204165 86
1776204170 86
1776204175 86
```
</details>

---

