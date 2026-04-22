---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 11:31:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 7 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1776871219 28
1776871224 28
1776871229 28
1776871234 28
1776871239 28
1776871244 28
1776871249 28
1776871254 26
1776871259 26
1776871264 26
1776871269 26
1776871274 26
1776871279 26
1776871284 26
1776871289 26
1776871294 26
1776871299 26
1776871304 26
1776871309 26
1776871314 26
```
</details>

---

