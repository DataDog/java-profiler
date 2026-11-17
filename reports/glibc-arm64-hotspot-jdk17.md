---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 13:06:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 13 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (3 unique values: 23-59 cores)</summary>

```
1794938497 23
1794938502 23
1794938507 23
1794938512 23
1794938517 23
1794938522 23
1794938527 23
1794938532 23
1794938537 23
1794938542 59
1794938547 59
1794938552 28
1794938557 28
1794938562 28
1794938567 28
1794938572 28
1794938577 28
1794938582 28
1794938587 28
1794938592 28
```
</details>

---

