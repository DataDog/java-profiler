---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 09:45:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (5 unique values: 47-67 cores)</summary>

```
1793281279 47
1793281284 47
1793281289 55
1793281294 55
1793281299 55
1793281304 55
1793281309 55
1793281314 55
1793281319 67
1793281324 67
1793281329 67
1793281334 64
1793281339 64
1793281344 64
1793281349 64
1793281354 64
1793281359 64
1793281364 64
1793281369 64
1793281374 62
```
</details>

---

