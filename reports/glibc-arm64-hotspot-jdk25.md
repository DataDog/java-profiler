---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 05:22:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 15 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (4 unique values: 45-52 cores)</summary>

```
1787044567 45
1787044572 45
1787044577 45
1787044582 45
1787044587 45
1787044592 45
1787044597 45
1787044602 45
1787044607 47
1787044612 47
1787044617 47
1787044622 52
1787044627 52
1787044632 47
1787044637 47
1787044642 47
1787044647 47
1787044652 47
1787044657 47
1787044662 47
```
</details>

---

