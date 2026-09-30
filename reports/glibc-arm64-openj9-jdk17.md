---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 08:24:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790770754 48
1790770759 48
1790770764 48
1790770769 48
1790770774 48
1790770779 48
1790770784 48
1790770789 48
1790770794 48
1790770799 48
1790770804 48
1790770809 48
1790770814 48
1790770819 48
1790770824 48
1790770829 48
1790770834 48
1790770839 48
1790770844 48
1790770849 48
```
</details>

---

