---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-06 04:52:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 21-27 cores)</summary>

```
1772790364 23
1772790369 23
1772790374 21
1772790379 21
1772790384 21
1772790389 21
1772790394 21
1772790399 21
1772790404 21
1772790409 21
1772790414 21
1772790419 21
1772790424 25
1772790429 25
1772790434 25
1772790439 27
1772790444 27
1772790449 27
1772790454 27
1772790459 27
```
</details>

---

