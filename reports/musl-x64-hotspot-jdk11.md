---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:47:46 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 954 |
| Sample Rate | 15.90/sec |
| Health Score | 994% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1795099222 68
1795099227 68
1795099232 68
1795099237 68
1795099242 68
1795099247 68
1795099252 68
1795099257 68
1795099262 68
1795099267 68
1795099272 66
1795099277 66
1795099282 66
1795099287 66
1795099292 66
1795099297 66
1795099302 66
1795099307 66
1795099312 66
1795099317 66
```
</details>

---

