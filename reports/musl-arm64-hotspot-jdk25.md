---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 17:14:29 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 16 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795558143 48
1795558148 48
1795558153 48
1795558158 48
1795558163 48
1795558168 48
1795558173 64
1795558178 64
1795558183 64
1795558188 64
1795558193 64
1795558199 64
1795558204 64
1795558209 64
1795558214 64
1795558219 64
1795558224 64
1795558229 64
1795558234 64
1795558239 64
```
</details>

---

