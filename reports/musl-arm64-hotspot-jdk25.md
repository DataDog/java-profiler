---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 07:35:21 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794832260 48
1794832265 48
1794832270 48
1794832275 48
1794832280 48
1794832285 48
1794832290 48
1794832295 48
1794832300 48
1794832305 48
1794832310 48
1794832315 43
1794832320 43
1794832325 43
1794832330 43
1794832335 43
1794832340 43
1794832345 43
1794832350 43
1794832355 43
```
</details>

---

