---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-27 00:56:04 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1787806368 43
1787806373 43
1787806378 43
1787806383 43
1787806388 43
1787806393 43
1787806398 43
1787806403 43
1787806408 43
1787806413 43
1787806418 43
1787806423 43
1787806428 43
1787806433 43
1787806438 43
1787806443 43
1787806448 40
1787806453 40
1787806458 40
1787806463 40
```
</details>

---

