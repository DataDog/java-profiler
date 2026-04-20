---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 07:58:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1776686076 60
1776686081 60
1776686086 60
1776686092 60
1776686097 60
1776686102 64
1776686107 64
1776686112 64
1776686117 64
1776686122 64
1776686127 64
1776686132 64
1776686137 64
1776686142 64
1776686147 64
1776686152 64
1776686157 64
1776686162 64
1776686167 64
1776686172 64
```
</details>

---

