---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:15:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795691186 64
1795691191 64
1795691196 64
1795691201 64
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
```
</details>

---

