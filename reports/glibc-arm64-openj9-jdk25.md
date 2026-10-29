---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 09:55:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 11 |
| Allocations | 124 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 25-29 cores)</summary>

```
1793281851 29
1793281856 29
1793281861 29
1793281866 29
1793281871 29
1793281876 29
1793281881 29
1793281886 29
1793281891 29
1793281896 29
1793281901 29
1793281906 29
1793281911 29
1793281916 29
1793281921 29
1793281926 29
1793281931 29
1793281936 29
1793281941 29
1793281946 29
```
</details>

---

