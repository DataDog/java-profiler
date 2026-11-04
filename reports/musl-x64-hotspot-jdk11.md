---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 16:24:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 69-75 cores)</summary>

```
1793827195 75
1793827201 75
1793827206 75
1793827211 75
1793827216 69
1793827221 69
1793827226 69
1793827231 69
1793827236 69
1793827241 69
1793827246 69
1793827251 69
1793827256 69
1793827261 69
1793827266 69
1793827271 69
1793827276 69
1793827281 69
1793827286 69
1793827291 69
```
</details>

---

