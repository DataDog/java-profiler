---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 08:35:38 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 9 |
| Allocations | 104 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794490191 32
1794490196 32
1794490201 32
1794490206 32
1794490211 32
1794490216 32
1794490221 32
1794490226 32
1794490231 32
1794490236 32
1794490241 32
1794490246 32
1794490251 32
1794490256 32
1794490261 32
1794490266 32
1794490271 32
1794490276 32
1794490281 32
1794490286 32
```
</details>

---

