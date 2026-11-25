---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1795605221 55
1795605226 64
1795605231 64
1795605236 55
1795605241 55
1795605246 55
1795605251 55
1795605256 55
1795605261 55
1795605266 55
1795605271 55
1795605276 55
1795605281 55
1795605286 55
1795605291 55
1795605296 55
1795605301 55
1795605306 55
1795605311 55
1795605316 55
```
</details>

---

