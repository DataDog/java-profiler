---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 22:10:40 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 923 |
| Sample Rate | 15.38/sec |
| Health Score | 961% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794625654 44
1794625659 44
1794625664 44
1794625669 44
1794625674 44
1794625679 44
1794625684 44
1794625689 44
1794625694 44
1794625699 44
1794625704 44
1794625709 44
1794625714 44
1794625719 44
1794625724 44
1794625729 44
1794625734 44
1794625739 44
1794625744 44
1794625749 44
```
</details>

---

