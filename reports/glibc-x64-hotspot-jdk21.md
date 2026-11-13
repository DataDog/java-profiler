---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:26:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794572512 30
1794572517 30
1794572522 30
1794572527 30
1794572532 30
1794572537 30
1794572542 30
1794572547 30
1794572552 32
1794572557 32
1794572562 30
1794572567 30
1794572572 30
1794572577 30
1794572582 30
1794572587 30
1794572592 30
1794572597 30
1794572602 30
1794572607 30
```
</details>

---

