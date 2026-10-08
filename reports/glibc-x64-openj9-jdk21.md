---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:53:14 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 11 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 88-96 cores)</summary>

```
1791470886 96
1791470891 96
1791470896 96
1791470901 96
1791470906 96
1791470911 92
1791470916 92
1791470921 92
1791470926 92
1791470931 92
1791470936 92
1791470941 92
1791470946 92
1791470951 92
1791470956 92
1791470961 92
1791470966 88
1791470971 88
1791470976 88
1791470981 88
```
</details>

---

