---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 08:24:38 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1790770866 40
1790770871 40
1790770876 40
1790770881 40
1790770886 40
1790770891 40
1790770896 40
1790770901 40
1790770906 40
1790770911 40
1790770917 40
1790770922 40
1790770927 40
1790770932 40
1790770937 40
1790770942 40
1790770947 40
1790770952 40
1790770957 40
1790770962 40
```
</details>

---

