---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 00:04:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (5 unique values: 47-57 cores)</summary>

```
1795669255 57
1795669260 57
1795669265 57
1795669270 57
1795669275 57
1795669280 55
1795669285 55
1795669290 55
1795669295 55
1795669300 53
1795669305 53
1795669310 53
1795669315 55
1795669320 55
1795669325 55
1795669330 55
1795669335 55
1795669340 55
1795669345 53
1795669350 53
```
</details>

---

