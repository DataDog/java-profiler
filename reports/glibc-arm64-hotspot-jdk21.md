---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 05:22:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1787044542 45
1787044547 45
1787044552 45
1787044557 45
1787044562 45
1787044567 45
1787044572 45
1787044577 45
1787044582 45
1787044587 45
1787044592 45
1787044597 45
1787044602 45
1787044607 45
1787044612 45
1787044617 45
1787044622 45
1787044627 45
1787044632 48
1787044637 48
```
</details>

---

