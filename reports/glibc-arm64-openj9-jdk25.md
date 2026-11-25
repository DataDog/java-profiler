---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:50:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795628802 64
1795628807 64
1795628812 64
1795628817 64
1795628822 64
1795628827 64
1795628832 64
1795628837 64
1795628842 64
1795628847 64
1795628852 64
1795628857 64
1795628862 64
1795628867 64
1795628872 64
1795628877 64
1795628882 64
1795628887 64
1795628892 64
1795628897 64
```
</details>

---

