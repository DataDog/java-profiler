---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 15:22:37 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 16 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1794341831 43
1794341836 43
1794341841 43
1794341846 43
1794341851 43
1794341856 43
1794341861 43
1794341866 47
1794341871 47
1794341876 47
1794341881 47
1794341886 47
1794341891 47
1794341896 47
1794341901 47
1794341906 47
1794341911 47
1794341916 47
1794341921 51
1794341926 51
```
</details>

---

