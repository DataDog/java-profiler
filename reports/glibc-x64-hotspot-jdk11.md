---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 16:29:16 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 84-88 cores)</summary>

```
1777321284 88
1777321289 88
1777321294 88
1777321299 88
1777321304 86
1777321309 86
1777321314 86
1777321319 86
1777321324 84
1777321329 84
1777321334 84
1777321339 84
1777321344 84
1777321349 84
1777321354 84
1777321359 84
1777321364 84
1777321369 86
1777321374 86
1777321379 86
```
</details>

---

