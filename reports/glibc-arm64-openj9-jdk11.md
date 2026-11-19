---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 06:28:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 14 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 36-38 cores)</summary>

```
1795087383 38
1795087388 38
1795087393 38
1795087398 36
1795087403 36
1795087408 36
1795087413 36
1795087418 36
1795087423 36
1795087428 36
1795087433 36
1795087438 36
1795087443 36
1795087448 36
1795087453 37
1795087458 37
1795087463 38
1795087468 38
1795087473 38
1795087478 38
```
</details>

---

