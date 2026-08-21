---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 19:10:08 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1787353570 24
1787353575 24
1787353580 24
1787353585 29
1787353590 29
1787353595 29
1787353600 29
1787353605 29
1787353610 29
1787353615 29
1787353620 29
1787353625 29
1787353630 29
1787353635 29
1787353640 29
1787353645 29
1787353650 29
1787353655 34
1787353660 34
1787353665 34
```
</details>

---

