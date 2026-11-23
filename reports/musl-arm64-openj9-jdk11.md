---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 08:37:36 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 11 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 36-52 cores)</summary>

```
1795440803 52
1795440808 52
1795440813 52
1795440818 52
1795440823 52
1795440828 52
1795440833 52
1795440838 36
1795440843 36
1795440848 36
1795440853 36
1795440858 36
1795440863 36
1795440868 36
1795440873 36
1795440878 36
1795440883 36
1795440888 36
1795440893 36
1795440898 36
```
</details>

---

