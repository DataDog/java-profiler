---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 21:38:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 8 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1787016836 43
1787016841 43
1787016846 43
1787016851 43
1787016856 43
1787016861 43
1787016866 43
1787016871 43
1787016876 43
1787016881 43
1787016886 43
1787016891 43
1787016896 43
1787016901 43
1787016906 38
1787016911 38
1787016916 38
1787016921 38
1787016926 38
1787016931 38
```
</details>

---

