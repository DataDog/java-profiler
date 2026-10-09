---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 06:38:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791541871 43
1791541876 43
1791541881 48
1791541886 48
1791541891 48
1791541896 48
1791541901 48
1791541906 48
1791541911 48
1791541916 48
1791541921 48
1791541926 48
1791541931 48
1791541936 48
1791541941 48
1791541946 48
1791541951 48
1791541956 48
1791541961 48
1791541966 48
```
</details>

---

