---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-02-02 15:17:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770063256 24
1770063261 24
1770063266 24
1770063271 24
1770063276 24
1770063281 24
1770063286 24
1770063291 24
1770063296 24
1770063301 24
1770063306 24
1770063311 24
1770063316 24
1770063321 24
1770063326 24
1770063331 24
1770063336 24
1770063341 24
1770063346 24
1770063351 24
```
</details>

---

