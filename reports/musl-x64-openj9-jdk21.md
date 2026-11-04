---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 34-53 cores)</summary>

```
1793830718 53
1793830723 53
1793830728 53
1793830733 53
1793830738 53
1793830743 53
1793830748 53
1793830753 53
1793830758 53
1793830763 53
1793830768 53
1793830773 53
1793830778 53
1793830783 53
1793830788 53
1793830793 53
1793830798 53
1793830803 53
1793830808 36
1793830813 36
```
</details>

---

