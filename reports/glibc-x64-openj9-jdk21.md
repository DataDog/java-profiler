---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 20:59:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 37-44 cores)</summary>

```
1793148885 37
1793148890 39
1793148895 39
1793148900 39
1793148905 44
1793148910 44
1793148915 44
1793148920 44
1793148925 44
1793148930 44
1793148935 44
1793148940 44
1793148945 44
1793148950 44
1793148955 44
1793148960 44
1793148965 44
1793148970 44
1793148975 44
1793148980 44
```
</details>

---

