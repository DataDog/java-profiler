---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-28 09:57:16 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1777384226 28
1777384231 28
1777384236 28
1777384241 28
1777384246 23
1777384251 23
1777384256 27
1777384261 27
1777384266 27
1777384271 27
1777384276 27
1777384281 27
1777384286 27
1777384291 27
1777384296 27
1777384301 27
1777384306 27
1777384311 27
1777384316 27
1777384321 27
```
</details>

---

