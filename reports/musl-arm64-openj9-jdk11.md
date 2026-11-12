---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:33:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 10 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 36-43 cores)</summary>

```
1794497271 43
1794497276 43
1794497281 43
1794497286 43
1794497291 43
1794497296 43
1794497301 43
1794497306 43
1794497311 43
1794497316 38
1794497321 38
1794497326 38
1794497331 38
1794497336 38
1794497341 38
1794497346 36
1794497351 36
1794497356 39
1794497361 39
1794497366 43
```
</details>

---

