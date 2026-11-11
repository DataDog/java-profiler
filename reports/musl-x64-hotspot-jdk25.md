---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 16:04:55 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 80-96 cores)</summary>

```
1794430802 96
1794430807 96
1794430812 96
1794430817 96
1794430822 96
1794430827 96
1794430832 96
1794430837 96
1794430842 96
1794430847 96
1794430852 96
1794430857 80
1794430862 80
1794430867 80
1794430872 80
1794430877 80
1794430882 80
1794430887 80
1794430892 80
1794430897 80
```
</details>

---

