---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 08:15:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1092 |
| Sample Rate | 18.20/sec |
| Health Score | 1137% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1794748194 63
1794748199 63
1794748204 63
1794748209 63
1794748214 63
1794748219 63
1794748224 63
1794748229 63
1794748234 61
1794748239 61
1794748244 61
1794748249 61
1794748254 61
1794748259 61
1794748264 61
1794748269 61
1794748274 63
1794748279 63
1794748284 63
1794748289 63
```
</details>

---

