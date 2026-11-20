---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 05:56:26 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (4 unique values: 36-40 cores)</summary>

```
1795171826 39
1795171831 39
1795171836 39
1795171841 39
1795171846 39
1795171851 39
1795171856 39
1795171861 39
1795171866 36
1795171871 36
1795171876 36
1795171881 36
1795171886 38
1795171891 38
1795171896 40
1795171901 40
1795171906 40
1795171911 40
1795171916 40
1795171921 40
```
</details>

---

