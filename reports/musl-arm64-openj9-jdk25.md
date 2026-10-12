---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-12 05:09:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 48-64 cores)</summary>

```
1791795891 48
1791795896 48
1791795901 48
1791795906 48
1791795911 48
1791795916 48
1791795921 53
1791795926 53
1791795931 53
1791795936 53
1791795941 53
1791795946 53
1791795951 53
1791795956 53
1791795961 53
1791795966 53
1791795971 53
1791795976 53
1791795981 53
1791795986 53
```
</details>

---

