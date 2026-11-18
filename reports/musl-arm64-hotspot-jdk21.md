---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:25:45 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 16 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1795015274 41
1795015279 41
1795015284 41
1795015289 41
1795015294 46
1795015299 46
1795015304 46
1795015309 46
1795015314 46
1795015319 46
1795015324 46
1795015329 46
1795015334 46
1795015339 46
1795015344 46
1795015349 46
1795015354 46
1795015359 46
1795015364 46
1795015369 46
```
</details>

---

