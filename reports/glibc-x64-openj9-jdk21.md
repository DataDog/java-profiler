---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:31:13 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (6 unique values: 68-82 cores)</summary>

```
1776695012 75
1776695017 75
1776695022 75
1776695027 70
1776695032 70
1776695037 70
1776695042 70
1776695047 70
1776695052 70
1776695058 70
1776695063 70
1776695068 70
1776695073 70
1776695078 70
1776695083 70
1776695088 70
1776695093 70
1776695098 70
1776695103 68
1776695108 68
```
</details>

---

