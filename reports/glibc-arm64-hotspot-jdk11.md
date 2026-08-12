---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 08:46:04 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 13 |
| Allocations | 160 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1786538517 51
1786538522 51
1786538527 51
1786538532 51
1786538537 51
1786538542 51
1786538547 51
1786538552 51
1786538557 51
1786538562 51
1786538567 51
1786538572 51
1786538577 51
1786538582 51
1786538587 51
1786538592 51
1786538597 51
1786538602 51
1786538607 64
1786538612 64
```
</details>

---

