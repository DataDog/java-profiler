---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 07:19:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (7 unique values: 71-89 cores)</summary>

```
1795004185 78
1795004190 78
1795004195 76
1795004200 76
1795004205 73
1795004210 73
1795004215 73
1795004220 71
1795004225 71
1795004230 80
1795004235 80
1795004240 84
1795004245 84
1795004250 84
1795004255 84
1795004260 84
1795004265 84
1795004270 84
1795004275 84
1795004280 84
```
</details>

---

