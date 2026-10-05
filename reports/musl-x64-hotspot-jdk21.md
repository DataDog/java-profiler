---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 71-81 cores)</summary>

```
1791191807 71
1791191812 71
1791191817 71
1791191822 71
1791191827 71
1791191832 71
1791191837 71
1791191842 71
1791191848 81
1791191853 81
1791191858 81
1791191863 81
1791191868 78
1791191873 78
1791191878 78
1791191883 78
1791191888 78
1791191893 78
1791191898 78
1791191903 78
```
</details>

---

