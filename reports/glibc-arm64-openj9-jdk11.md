---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:56:09 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793357504 46
1793357509 46
1793357514 46
1793357519 48
1793357524 48
1793357529 48
1793357534 48
1793357539 43
1793357544 43
1793357549 43
1793357554 43
1793357559 43
1793357564 43
1793357569 43
1793357574 43
1793357579 43
1793357584 43
1793357589 43
1793357594 43
1793357599 43
```
</details>

---

