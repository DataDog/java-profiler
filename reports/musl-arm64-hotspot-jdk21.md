---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:36:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 48-56 cores)</summary>

```
1794357155 48
1794357160 48
1794357165 48
1794357170 48
1794357175 48
1794357180 48
1794357185 48
1794357190 48
1794357195 48
1794357200 48
1794357205 48
1794357210 48
1794357215 48
1794357220 48
1794357225 48
1794357230 48
1794357235 48
1794357240 56
1794357245 56
1794357250 56
```
</details>

---

