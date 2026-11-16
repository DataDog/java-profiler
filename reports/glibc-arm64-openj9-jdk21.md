---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 08:52:13 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794836821 51
1794836826 51
1794836831 51
1794836836 51
1794836841 51
1794836846 51
1794836851 51
1794836856 51
1794836861 51
1794836866 51
1794836871 51
1794836876 51
1794836881 51
1794836886 51
1794836891 51
1794836896 46
1794836901 46
1794836906 46
1794836911 46
1794836916 46
```
</details>

---

