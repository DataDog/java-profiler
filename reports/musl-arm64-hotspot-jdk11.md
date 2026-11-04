---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 16:24:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 10 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (1 unique values: 18-18 cores)</summary>

```
1793827198 18
1793827203 18
1793827208 18
1793827213 18
1793827218 18
1793827223 18
1793827228 18
1793827233 18
1793827238 18
1793827243 18
1793827248 18
1793827253 18
1793827258 18
1793827263 18
1793827268 18
1793827273 18
1793827278 18
1793827283 18
1793827288 18
1793827293 18
```
</details>

---

