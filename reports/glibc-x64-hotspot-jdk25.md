---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 07:58:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1776686021 24
1776686026 24
1776686031 24
1776686036 24
1776686041 28
1776686046 28
1776686051 23
1776686056 23
1776686061 23
1776686066 23
1776686071 23
1776686076 23
1776686081 23
1776686086 23
1776686091 23
1776686096 23
1776686101 23
1776686106 23
1776686111 23
1776686116 23
```
</details>

---

