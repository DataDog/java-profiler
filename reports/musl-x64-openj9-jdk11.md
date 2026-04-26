---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-26 15:52:41 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 914 |
| Sample Rate | 15.23/sec |
| Health Score | 952% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1777232884 96
1777232889 96
1777232894 96
1777232899 91
1777232904 91
1777232909 91
1777232914 91
1777232919 96
1777232924 96
1777232929 96
1777232934 96
1777232939 96
1777232944 96
1777232949 96
1777232954 94
1777232959 94
1777232964 94
1777232969 94
1777232974 96
1777232979 96
```
</details>

---

