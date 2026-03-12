---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-12 11:39:20 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 738 |
| Sample Rate | 12.30/sec |
| Health Score | 769% |
| Threads | 13 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (3 unique values: 58-63 cores)</summary>

```
1773329681 61
1773329686 61
1773329691 61
1773329696 61
1773329701 63
1773329706 63
1773329711 63
1773329716 63
1773329721 63
1773329726 63
1773329731 63
1773329736 58
1773329741 58
1773329746 58
1773329751 58
1773329756 58
1773329761 58
1773329766 58
1773329771 58
1773329776 58
```
</details>

---

