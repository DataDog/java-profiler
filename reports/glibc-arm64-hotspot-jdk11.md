---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 13:40:51 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 39-64 cores)</summary>

```
1787074517 64
1787074522 44
1787074527 44
1787074532 44
1787074537 44
1787074542 44
1787074547 44
1787074552 44
1787074557 39
1787074562 39
1787074567 39
1787074572 39
1787074577 39
1787074582 39
1787074587 39
1787074592 39
1787074597 39
1787074602 39
1787074607 39
1787074612 39
```
</details>

---

