---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-09 05:04:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 14 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1775724920 38
1775724925 38
1775724930 38
1775724935 38
1775724940 38
1775724945 38
1775724950 38
1775724955 38
1775724960 38
1775724965 38
1775724970 38
1775724975 38
1775724980 38
1775724985 38
1775724990 43
1775724995 43
1775725000 43
1775725005 43
1775725010 43
1775725015 43
```
</details>

---

