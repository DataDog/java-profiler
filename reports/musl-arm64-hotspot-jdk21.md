---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-03 00:57:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 12 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1788411200 14
1788411205 14
1788411210 14
1788411215 14
1788411220 14
1788411225 14
1788411230 14
1788411235 14
1788411240 14
1788411245 14
1788411250 14
1788411255 14
1788411260 14
1788411265 14
1788411270 14
1788411275 14
1788411280 14
1788411285 14
1788411290 14
1788411295 9
```
</details>

---

