---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 442 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 21.63/sec |
| Health Score | 1352% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1769702780 45
1769702785 45
1769702790 46
1769702795 46
1769702800 48
1769702805 48
1769702810 48
1769702815 48
1769702820 48
1769702825 48
1769702830 48
1769702835 48
1769702840 48
1769702845 48
1769702850 48
1769702855 48
1769702860 48
1769702865 48
1769702870 48
1769702875 48
```
</details>

---

