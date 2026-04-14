---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-14 11:42:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (6 unique values: 72-91 cores)</summary>

```
1776180935 85
1776180940 91
1776180945 91
1776180950 87
1776180955 87
1776180960 87
1776180965 87
1776180970 87
1776180975 85
1776180980 85
1776180985 80
1776180990 80
1776180995 80
1776181000 82
1776181005 82
1776181010 82
1776181015 82
1776181020 82
1776181025 80
1776181030 80
```
</details>

---

