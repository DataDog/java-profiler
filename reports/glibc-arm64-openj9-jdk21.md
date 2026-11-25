---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:50:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 44-60 cores)</summary>

```
1795628777 48
1795628782 48
1795628787 48
1795628792 44
1795628797 44
1795628802 44
1795628807 44
1795628812 44
1795628817 60
1795628822 60
1795628827 60
1795628832 60
1795628837 60
1795628842 60
1795628847 60
1795628852 60
1795628857 60
1795628862 60
1795628867 60
1795628872 60
```
</details>

---

