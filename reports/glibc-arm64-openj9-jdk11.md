---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-23 21:24:26 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787534403 43
1787534408 43
1787534413 43
1787534418 43
1787534423 43
1787534428 43
1787534433 48
1787534438 48
1787534443 48
1787534448 48
1787534453 48
1787534458 48
1787534463 48
1787534468 48
1787534473 43
1787534478 43
1787534483 43
1787534488 43
1787534493 43
1787534498 43
```
</details>

---

