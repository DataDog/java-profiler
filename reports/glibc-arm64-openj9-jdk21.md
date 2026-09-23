---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:09:12 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790168694 40
1790168699 40
1790168704 40
1790168709 40
1790168714 40
1790168719 40
1790168724 40
1790168729 40
1790168734 40
1790168739 45
1790168744 45
1790168749 45
1790168754 45
1790168759 45
1790168764 45
1790168769 45
1790168774 45
1790168779 45
1790168784 45
1790168789 45
```
</details>

---

