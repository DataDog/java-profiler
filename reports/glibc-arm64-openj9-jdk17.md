---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-14 10:14:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 12 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1786716683 64
1786716688 64
1786716693 64
1786716698 64
1786716703 64
1786716708 64
1786716713 64
1786716718 64
1786716723 44
1786716728 44
1786716733 44
1786716739 44
1786716744 44
1786716749 44
1786716754 44
1786716759 44
1786716764 44
1786716769 44
1786716774 44
1786716779 44
```
</details>

---

