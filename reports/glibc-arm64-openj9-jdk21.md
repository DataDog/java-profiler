---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:38:25 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1792834347 41
1792834352 41
1792834357 41
1792834362 41
1792834367 41
1792834372 41
1792834377 41
1792834382 41
1792834387 41
1792834392 46
1792834397 46
1792834402 51
1792834407 51
1792834412 46
1792834417 46
1792834422 46
1792834427 46
1792834432 46
1792834437 46
1792834442 46
```
</details>

---

