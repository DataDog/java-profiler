---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 14:05:04 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 67-87 cores)</summary>

```
1777312776 83
1777312781 83
1777312786 87
1777312791 87
1777312796 69
1777312801 69
1777312806 69
1777312811 69
1777312816 69
1777312821 69
1777312826 67
1777312831 67
1777312836 67
1777312841 67
1777312846 67
1777312851 67
1777312856 67
1777312861 69
1777312866 69
1777312872 78
```
</details>

---

