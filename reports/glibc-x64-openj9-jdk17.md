---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:26:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 68-76 cores)</summary>

```
1794572502 76
1794572507 76
1794572513 76
1794572518 76
1794572523 76
1794572528 76
1794572533 76
1794572538 76
1794572543 76
1794572548 76
1794572553 68
1794572558 68
1794572563 68
1794572568 68
1794572573 68
1794572578 68
1794572583 68
1794572588 68
1794572593 68
1794572598 68
```
</details>

---

