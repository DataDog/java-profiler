---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:28:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 12 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 69-71 cores)</summary>

```
1795015344 69
1795015349 69
1795015354 69
1795015359 69
1795015364 69
1795015369 69
1795015374 69
1795015379 69
1795015384 69
1795015389 69
1795015394 71
1795015399 71
1795015404 71
1795015409 71
1795015414 71
1795015419 71
1795015424 71
1795015429 71
1795015434 71
1795015439 71
```
</details>

---

