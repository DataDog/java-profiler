---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:48:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (4 unique values: 61-68 cores)</summary>

```
1795632215 66
1795632220 66
1795632225 66
1795632230 66
1795632235 66
1795632240 66
1795632245 66
1795632250 66
1795632255 64
1795632260 64
1795632265 64
1795632270 64
1795632275 68
1795632280 68
1795632285 61
1795632290 61
1795632295 61
1795632300 61
1795632305 61
1795632310 61
```
</details>

---

