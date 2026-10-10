---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-10 05:51:04 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791625621 32
1791625626 32
1791625631 32
1791625636 32
1791625641 32
1791625646 32
1791625651 32
1791625656 32
1791625661 32
1791625666 32
1791625671 32
1791625676 32
1791625681 32
1791625686 32
1791625691 32
1791625696 32
1791625701 32
1791625706 32
1791625711 32
1791625716 32
```
</details>

---

