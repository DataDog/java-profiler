---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 11:20:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 38-67 cores)</summary>

```
1795796205 67
1795796210 67
1795796215 67
1795796220 67
1795796225 38
1795796230 38
1795796235 38
1795796240 38
1795796245 38
1795796250 38
1795796255 38
1795796260 38
1795796265 38
1795796270 38
1795796275 38
1795796280 38
1795796285 38
1795796290 38
1795796295 38
1795796300 38
```
</details>

---

