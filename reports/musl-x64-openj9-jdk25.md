---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:52:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 13 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 25-60 cores)</summary>

```
1772790384 25
1772790389 29
1772790394 29
1772790399 29
1772790404 29
1772790409 29
1772790414 29
1772790419 60
1772790424 60
1772790429 60
1772790434 60
1772790439 60
1772790444 55
1772790449 55
1772790454 55
1772790459 55
1772790464 55
1772790469 55
1772790474 55
1772790479 55
```
</details>

---

