---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:16 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 14 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794326110 48
1794326115 48
1794326120 48
1794326125 48
1794326130 48
1794326135 48
1794326140 48
1794326145 43
1794326150 43
1794326155 43
1794326160 43
1794326166 43
1794326171 43
1794326176 43
1794326181 43
1794326186 43
1794326191 43
1794326196 43
1794326201 43
1794326206 43
```
</details>

---

