---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 07:20:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 13 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (5 unique values: 33-43 cores)</summary>

```
1790853370 33
1790853375 33
1790853380 33
1790853385 38
1790853390 38
1790853395 38
1790853400 38
1790853405 40
1790853410 40
1790853415 40
1790853420 40
1790853425 42
1790853430 42
1790853435 42
1790853440 42
1790853445 42
1790853450 42
1790853455 42
1790853460 42
1790853465 43
```
</details>

---

