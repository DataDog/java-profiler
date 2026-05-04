---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-03 21:22:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 15 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857388 64
1777857393 64
1777857398 64
1777857403 64
1777857408 64
1777857413 64
1777857418 64
1777857423 64
1777857428 64
1777857433 64
1777857438 64
1777857443 64
1777857448 64
1777857453 64
1777857458 64
1777857463 64
1777857468 64
1777857473 64
1777857478 64
1777857483 64
```
</details>

---

