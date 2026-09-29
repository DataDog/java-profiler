---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 11:52:32 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 11 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1790696831 27
1790696836 27
1790696841 27
1790696846 27
1790696851 27
1790696856 27
1790696861 27
1790696866 27
1790696871 27
1790696876 27
1790696881 27
1790696886 27
1790696891 27
1790696896 22
1790696901 22
1790696906 22
1790696911 22
1790696916 22
1790696921 22
1790696926 22
```
</details>

---

