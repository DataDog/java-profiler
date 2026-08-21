---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 07:48:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 43-49 cores)</summary>

```
1787312640 45
1787312645 45
1787312650 45
1787312655 47
1787312660 47
1787312665 47
1787312670 47
1787312675 47
1787312680 47
1787312685 47
1787312690 49
1787312695 49
1787312700 49
1787312705 49
1787312710 49
1787312715 49
1787312720 49
1787312725 49
1787312730 49
1787312735 49
```
</details>

---

