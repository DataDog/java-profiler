---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:00:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793721210 48
1793721215 48
1793721220 48
1793721225 48
1793721230 48
1793721235 48
1793721240 48
1793721245 48
1793721250 48
1793721255 48
1793721260 48
1793721265 48
1793721270 48
1793721275 48
1793721280 43
1793721285 43
1793721290 43
1793721295 43
1793721300 43
1793721305 43
```
</details>

---

