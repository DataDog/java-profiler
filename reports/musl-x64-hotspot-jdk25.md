---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:07:56 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1795014205 62
1795014210 62
1795014215 62
1795014220 62
1795014225 62
1795014230 62
1795014235 62
1795014240 62
1795014245 62
1795014250 62
1795014255 62
1795014260 64
1795014265 64
1795014270 55
1795014275 55
1795014280 55
1795014285 55
1795014290 55
1795014295 55
1795014300 55
```
</details>

---

