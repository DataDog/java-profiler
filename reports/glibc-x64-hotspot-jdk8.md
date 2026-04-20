---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-20 11:41:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1776699112 27
1776699117 27
1776699122 27
1776699127 27
1776699132 27
1776699137 32
1776699142 32
1776699147 32
1776699152 32
1776699157 32
1776699162 32
1776699167 32
1776699172 32
1776699177 32
1776699182 32
1776699187 32
1776699192 32
1776699197 32
1776699202 32
1776699207 32
```
</details>

---

