---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 12:01:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 21-25 cores)</summary>

```
1776355123 23
1776355128 23
1776355133 21
1776355138 21
1776355143 21
1776355148 21
1776355153 21
1776355158 21
1776355163 21
1776355168 21
1776355173 23
1776355178 23
1776355183 23
1776355188 23
1776355193 23
1776355198 23
1776355203 23
1776355208 23
1776355213 23
1776355218 23
```
</details>

---

