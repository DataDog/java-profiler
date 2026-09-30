---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 08:24:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 54-70 cores)</summary>

```
1790770759 54
1790770764 54
1790770769 54
1790770774 54
1790770779 54
1790770784 70
1790770789 70
1790770794 70
1790770799 70
1790770804 70
1790770809 70
1790770814 70
1790770819 70
1790770824 70
1790770829 70
1790770834 70
1790770839 70
1790770844 70
1790770849 70
1790770854 70
```
</details>

---

