---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 16:19:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 77-81 cores)</summary>

```
1790885697 77
1790885702 77
1790885707 77
1790885712 77
1790885717 77
1790885722 77
1790885727 77
1790885732 81
1790885737 81
1790885742 81
1790885747 81
1790885752 81
1790885757 81
1790885762 81
1790885767 81
1790885772 81
1790885777 81
1790885782 81
1790885787 81
1790885792 81
```
</details>

---

