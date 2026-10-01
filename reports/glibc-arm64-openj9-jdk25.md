---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:20:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790853350 38
1790853355 38
1790853360 43
1790853365 43
1790853370 38
1790853375 38
1790853380 38
1790853385 38
1790853390 38
1790853395 38
1790853400 38
1790853405 38
1790853410 38
1790853415 38
1790853420 43
1790853425 43
1790853430 43
1790853435 43
1790853440 43
1790853445 43
```
</details>

---

