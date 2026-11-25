---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 08:34:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 30-33 cores)</summary>

```
1795613424 30
1795613429 30
1795613434 30
1795613439 30
1795613444 30
1795613449 30
1795613454 30
1795613459 30
1795613464 30
1795613469 30
1795613474 30
1795613479 30
1795613484 30
1795613489 30
1795613494 30
1795613499 33
1795613504 33
1795613509 33
1795613514 33
1795613519 33
```
</details>

---

