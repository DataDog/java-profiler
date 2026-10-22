---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 11:42:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 63-84 cores)</summary>

```
1792683211 64
1792683216 64
1792683221 66
1792683226 66
1792683231 66
1792683236 66
1792683241 66
1792683246 63
1792683251 63
1792683256 63
1792683261 63
1792683266 63
1792683271 63
1792683276 84
1792683281 84
1792683286 84
1792683291 84
1792683296 84
1792683301 84
1792683306 84
```
</details>

---

