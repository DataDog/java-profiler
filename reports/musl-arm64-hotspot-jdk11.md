---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 05:22:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1787044537 45
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
```
</details>

---

