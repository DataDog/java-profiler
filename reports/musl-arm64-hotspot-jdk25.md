---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:11:46 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795691196 47
1795691201 47
1795691206 64
1795691211 64
1795691216 64
1795691221 64
1795691226 64
1795691231 64
1795691236 64
1795691241 64
1795691246 64
1795691251 64
1795691256 64
1795691261 64
1795691266 64
1795691271 64
1795691276 64
1795691281 64
1795691286 64
1795691291 64
```
</details>

---

