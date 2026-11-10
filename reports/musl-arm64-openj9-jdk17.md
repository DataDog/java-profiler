---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 14 |
| Allocations | 100 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794326125 48
1794326130 48
1794326135 48
1794326140 48
1794326145 48
1794326150 48
1794326155 48
1794326160 43
1794326165 43
1794326170 43
1794326175 43
1794326180 43
1794326185 43
1794326190 43
1794326195 43
1794326200 43
1794326205 43
1794326210 43
1794326215 43
1794326220 43
```
</details>

---

