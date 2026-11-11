---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:36:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 12 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794357155 40
1794357160 40
1794357165 40
1794357170 40
1794357175 40
1794357180 40
1794357185 40
1794357190 40
1794357195 40
1794357200 40
1794357205 40
1794357210 40
1794357215 40
1794357220 40
1794357225 40
1794357230 40
1794357235 40
1794357240 40
1794357245 40
1794357250 35
```
</details>

---

