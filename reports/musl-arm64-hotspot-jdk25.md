---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 05:47:57 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795344224 59
1795344230 59
1795344235 59
1795344240 59
1795344245 59
1795344250 64
1795344255 64
1795344260 64
1795344265 59
1795344270 59
1795344275 59
1795344280 59
1795344285 59
1795344290 59
1795344295 59
1795344300 59
1795344305 59
1795344310 59
1795344315 59
1795344320 59
```
</details>

---

