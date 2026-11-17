---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:50:08 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 15 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 31-51 cores)</summary>

```
1794933922 31
1794933927 31
1794933932 31
1794933937 31
1794933942 31
1794933947 31
1794933952 51
1794933957 51
1794933962 51
1794933967 51
1794933972 51
1794933977 51
1794933982 51
1794933987 51
1794933992 51
1794933997 51
1794934002 51
1794934007 51
1794934012 51
1794934017 51
```
</details>

---

