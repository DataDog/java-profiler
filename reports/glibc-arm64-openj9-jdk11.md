---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 09:00:14 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 9 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 40-56 cores)</summary>

```
1778158394 56
1778158399 56
1778158404 56
1778158409 56
1778158414 40
1778158419 40
1778158424 40
1778158429 40
1778158434 40
1778158439 40
1778158444 40
1778158449 40
1778158454 40
1778158459 40
1778158464 40
1778158469 40
1778158474 40
1778158479 40
1778158484 40
1778158489 40
```
</details>

---

