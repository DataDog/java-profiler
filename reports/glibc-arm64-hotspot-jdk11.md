---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 16:16:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 9 |
| Allocations | 206 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793045260 46
1793045265 46
1793045270 46
1793045275 46
1793045280 46
1793045285 46
1793045290 46
1793045295 46
1793045300 46
1793045305 46
1793045310 46
1793045315 46
1793045320 46
1793045325 51
1793045330 51
1793045335 51
1793045340 51
1793045345 51
1793045350 51
1793045355 51
```
</details>

---

