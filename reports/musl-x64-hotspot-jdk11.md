---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-05 10:18:27 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1785939181 24
1785939186 24
1785939191 24
1785939196 24
1785939201 24
1785939206 24
1785939211 24
1785939216 24
1785939221 24
1785939226 24
1785939231 24
1785939236 24
1785939241 24
1785939246 24
1785939251 24
1785939256 32
1785939261 32
1785939266 32
1785939271 32
1785939276 32
```
</details>

---

