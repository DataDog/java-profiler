---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:06:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 53-61 cores)</summary>

```
1794592811 61
1794592816 61
1794592821 61
1794592826 61
1794592831 61
1794592836 61
1794592841 61
1794592846 61
1794592851 61
1794592856 61
1794592861 61
1794592866 53
1794592871 53
1794592876 53
1794592881 53
1794592886 53
1794592891 53
1794592896 53
1794592901 53
1794592906 53
```
</details>

---

