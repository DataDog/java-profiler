---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 07:58:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (4 unique values: 45-91 cores)</summary>

```
1776686025 45
1776686030 45
1776686036 57
1776686041 57
1776686046 57
1776686051 57
1776686056 56
1776686061 56
1776686066 56
1776686071 56
1776686076 56
1776686081 56
1776686086 56
1776686091 56
1776686096 91
1776686101 91
1776686106 91
1776686111 91
1776686116 91
1776686121 91
```
</details>

---

