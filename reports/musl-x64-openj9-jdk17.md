---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 08:24:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 90-96 cores)</summary>

```
1790770759 90
1790770764 90
1790770769 90
1790770774 90
1790770779 90
1790770784 90
1790770789 90
1790770794 90
1790770799 90
1790770804 90
1790770809 90
1790770814 90
1790770819 90
1790770824 90
1790770829 90
1790770834 90
1790770839 90
1790770844 90
1790770849 90
1790770854 96
```
</details>

---

