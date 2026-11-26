---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1795691231 91
1795691236 91
1795691241 91
1795691246 91
1795691251 91
1795691256 91
1795691261 91
1795691266 91
1795691271 91
1795691276 91
1795691281 91
1795691286 91
1795691291 91
1795691297 89
1795691302 89
1795691307 89
1795691312 89
1795691317 89
1795691322 89
1795691327 89
```
</details>

---

