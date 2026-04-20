---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 11:41:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1776699117 29
1776699122 29
1776699127 29
1776699132 29
1776699137 29
1776699142 29
1776699147 29
1776699152 29
1776699157 29
1776699162 29
1776699167 29
1776699172 29
1776699177 29
1776699182 27
1776699187 27
1776699192 27
1776699197 27
1776699202 27
1776699207 27
1776699212 27
```
</details>

---

