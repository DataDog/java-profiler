---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 12:45:52 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 14 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1794937234 51
1794937239 51
1794937244 51
1794937249 51
1794937254 51
1794937259 51
1794937264 51
1794937269 51
1794937274 51
1794937279 51
1794937284 51
1794937289 51
1794937294 51
1794937299 51
1794937304 51
1794937309 51
1794937315 51
1794937320 51
1794937325 51
1794937330 47
```
</details>

---

