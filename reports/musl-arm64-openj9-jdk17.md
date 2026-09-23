---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:27:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 9 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 13 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790173273 46
1790173278 46
1790173283 46
1790173288 46
1790173293 46
1790173298 46
1790173303 46
1790173308 46
1790173313 46
1790173318 46
1790173323 46
1790173328 46
1790173333 46
1790173338 46
1790173343 46
1790173348 48
1790173353 48
1790173358 48
1790173363 48
1790173368 48
```
</details>

---

