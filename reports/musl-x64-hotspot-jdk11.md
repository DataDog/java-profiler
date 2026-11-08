---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-08 06:01:09 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 950 |
| Sample Rate | 15.83/sec |
| Health Score | 989% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 30-63 cores)</summary>

```
1794135265 30
1794135270 30
1794135275 30
1794135280 30
1794135285 30
1794135290 30
1794135295 30
1794135300 30
1794135305 63
1794135310 63
1794135315 63
1794135320 63
1794135325 63
1794135330 63
1794135335 63
1794135340 63
1794135345 63
1794135350 63
1794135355 63
1794135360 63
```
</details>

---

