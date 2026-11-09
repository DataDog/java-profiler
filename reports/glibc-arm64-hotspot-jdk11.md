---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 10:36:28 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794238206 48
1794238211 48
1794238216 48
1794238221 48
1794238226 48
1794238231 48
1794238236 48
1794238241 48
1794238246 48
1794238251 46
1794238256 46
1794238261 46
1794238266 46
1794238271 46
1794238276 46
1794238281 46
1794238286 46
1794238291 46
1794238296 46
1794238301 46
```
</details>

---

