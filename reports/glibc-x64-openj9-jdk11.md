---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-01 12:28:06 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1788279648 44
1788279653 44
1788279658 44
1788279663 44
1788279668 44
1788279673 44
1788279678 44
1788279683 46
1788279688 46
1788279693 46
1788279698 46
1788279703 46
1788279708 46
1788279713 46
1788279718 46
1788279723 46
1788279728 46
1788279733 48
1788279738 48
1788279743 48
```
</details>

---

