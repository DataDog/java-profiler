---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 10:31:04 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 63-67 cores)</summary>

```
1778509513 63
1778509518 63
1778509523 63
1778509528 63
1778509533 63
1778509538 63
1778509543 63
1778509548 63
1778509553 63
1778509558 63
1778509563 63
1778509568 63
1778509573 63
1778509578 63
1778509583 63
1778509588 63
1778509593 63
1778509598 63
1778509603 63
1778509608 67
```
</details>

---

