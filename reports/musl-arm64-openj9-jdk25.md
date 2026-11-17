---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 13:29:12 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 11 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794939931 38
1794939936 38
1794939941 38
1794939946 38
1794939951 38
1794939956 38
1794939961 38
1794939966 38
1794939971 38
1794939976 51
1794939981 51
1794939986 51
1794939991 51
1794939996 51
1794940001 51
1794940006 51
1794940011 51
1794940016 51
1794940021 51
1794940026 51
```
</details>

---

