---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:27:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 12 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795627413 64
1795627418 64
1795627423 64
1795627428 64
1795627433 64
1795627438 64
1795627443 64
1795627448 64
1795627453 64
1795627458 64
1795627463 64
1795627468 64
1795627473 64
1795627478 64
1795627483 64
1795627488 64
1795627493 64
1795627498 64
1795627503 64
1795627508 64
```
</details>

---

