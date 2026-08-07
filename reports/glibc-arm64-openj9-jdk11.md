---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 17:19:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 8 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1786137274 30
1786137279 30
1786137284 30
1786137289 30
1786137294 30
1786137299 30
1786137304 30
1786137309 30
1786137314 30
1786137319 30
1786137324 30
1786137329 25
1786137334 25
1786137339 25
1786137344 25
1786137349 25
1786137354 25
1786137359 25
1786137364 25
1786137369 25
```
</details>

---

