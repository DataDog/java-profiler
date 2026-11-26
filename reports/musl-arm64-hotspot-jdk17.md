---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:15:15 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795691150 64
1795691155 64
1795691160 64
1795691165 64
1795691170 64
1795691175 64
1795691180 64
1795691185 33
1795691190 33
1795691195 33
1795691201 33
1795691206 33
1795691211 33
1795691216 33
1795691221 33
1795691226 33
1795691231 33
1795691236 33
1795691241 33
1795691246 33
```
</details>

---

