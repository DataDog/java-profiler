---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-09 09:27:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1794234136 76
1794234141 76
1794234146 76
1794234151 76
1794234156 76
1794234161 76
1794234166 76
1794234171 74
1794234176 74
1794234181 74
1794234186 74
1794234191 72
1794234196 72
1794234201 72
1794234206 72
1794234211 72
1794234216 72
1794234221 72
1794234226 72
1794234231 74
```
</details>

---

