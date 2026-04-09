---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-09 05:04:59 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1775724950 43
1775724955 43
1775724960 48
1775724965 48
1775724970 48
1775724975 48
1775724980 48
1775724985 48
1775724990 48
1775724995 48
1775725000 48
1775725005 48
1775725010 48
1775725015 48
1775725021 48
1775725026 48
1775725031 48
1775725036 48
1775725041 48
1775725046 48
```
</details>

---

