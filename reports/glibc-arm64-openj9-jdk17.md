---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-29 00:58:56 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 13 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787979353 34
1787979358 34
1787979363 34
1787979368 34
1787979373 34
1787979378 34
1787979383 34
1787979388 34
1787979393 34
1787979398 34
1787979403 34
1787979408 34
1787979413 34
1787979418 34
1787979423 34
1787979428 34
1787979433 34
1787979438 34
1787979443 34
1787979448 34
```
</details>

---

