---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-01 09:14:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 12 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1777640895 49
1777640900 49
1777640905 49
1777640910 49
1777640915 49
1777640920 49
1777640925 54
1777640930 54
1777640935 54
1777640940 54
1777640945 54
1777640950 54
1777640955 54
1777640960 54
1777640965 54
1777640970 54
1777640975 54
1777640980 54
1777640985 54
1777640990 54
```
</details>

---

