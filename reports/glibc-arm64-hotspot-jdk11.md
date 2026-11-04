---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 16:24:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793827203 48
1793827208 48
1793827213 48
1793827218 48
1793827223 48
1793827228 48
1793827233 48
1793827238 48
1793827243 48
1793827248 48
1793827253 48
1793827258 48
1793827263 48
1793827268 48
1793827273 48
1793827278 48
1793827283 48
1793827288 48
1793827293 48
1793827298 48
```
</details>

---

