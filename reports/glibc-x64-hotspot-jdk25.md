---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:51:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 75-92 cores)</summary>

```
1795538782 89
1795538787 87
1795538792 87
1795538797 87
1795538802 87
1795538807 87
1795538812 87
1795538817 87
1795538822 87
1795538827 87
1795538832 87
1795538837 87
1795538842 89
1795538847 89
1795538852 89
1795538857 89
1795538862 89
1795538867 89
1795538872 92
1795538877 92
```
</details>

---

