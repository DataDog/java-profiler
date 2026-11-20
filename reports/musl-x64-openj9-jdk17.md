---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 09:57:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 70-84 cores)</summary>

```
1795186245 70
1795186250 70
1795186255 70
1795186260 72
1795186265 72
1795186270 81
1795186275 81
1795186280 81
1795186285 81
1795186290 81
1795186295 81
1795186300 81
1795186305 81
1795186310 81
1795186315 84
1795186320 84
1795186325 84
1795186330 84
1795186335 84
1795186340 84
```
</details>

---

