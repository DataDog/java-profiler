---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:35:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1040 |
| Sample Rate | 17.33/sec |
| Health Score | 1083% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 26-38 cores)</summary>

```
1794997808 38
1794997813 38
1794997818 38
1794997823 38
1794997828 26
1794997833 26
1794997838 26
1794997843 26
1794997848 26
1794997853 26
1794997858 26
1794997863 26
1794997868 26
1794997873 26
1794997878 26
1794997883 26
1794997888 26
1794997894 26
1794997899 26
1794997904 26
```
</details>

---

