---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 19.57/sec |
| Health Score | 1223% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 981 |
| Sample Rate | 32.70/sec |
| Health Score | 2044% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 16-21 cores)</summary>

```
1769702691 19
1769702696 19
1769702701 19
1769702706 19
1769702711 21
1769702716 21
1769702721 21
1769702726 21
1769702731 21
1769702736 21
1769702741 16
1769702746 16
1769702751 16
1769702756 16
1769702761 16
1769702766 16
1769702771 16
1769702776 20
1769702781 20
1769702786 20
```
</details>

---

