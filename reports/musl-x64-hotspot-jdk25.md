---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:00:43 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1793721185 55
1793721190 55
1793721195 55
1793721200 55
1793721205 55
1793721210 55
1793721215 55
1793721220 55
1793721225 55
1793721230 55
1793721235 55
1793721240 55
1793721245 55
1793721250 55
1793721255 57
1793721260 57
1793721265 57
1793721270 57
1793721275 57
1793721280 57
```
</details>

---

