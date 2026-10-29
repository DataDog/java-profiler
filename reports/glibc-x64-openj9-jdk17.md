---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-29 13:49:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1793295806 81
1793295811 81
1793295816 81
1793295821 81
1793295826 81
1793295831 81
1793295836 81
1793295841 81
1793295846 81
1793295851 81
1793295856 81
1793295861 81
1793295866 81
1793295871 81
1793295876 81
1793295881 81
1793295886 81
1793295891 81
1793295897 81
1793295902 79
```
</details>

---

