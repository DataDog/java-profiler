---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 11:12:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 23.93/sec |
| Health Score | 1496% |
| Threads | 12 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 964 |
| Sample Rate | 32.13/sec |
| Health Score | 2008% |
| Threads | 13 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 52-57 cores)</summary>

```
1769702706 52
1769702711 52
1769702716 52
1769702721 52
1769702726 52
1769702731 52
1769702736 52
1769702741 56
1769702746 56
1769702751 56
1769702756 56
1769702761 56
1769702766 56
1769702771 56
1769702776 56
1769702781 56
1769702786 56
1769702791 56
1769702796 56
1769702801 56
```
</details>

---

