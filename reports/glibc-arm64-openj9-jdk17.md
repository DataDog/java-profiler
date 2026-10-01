---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 16:19:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790885687 48
1790885692 48
1790885697 48
1790885702 48
1790885707 48
1790885712 48
1790885717 48
1790885722 48
1790885727 48
1790885732 48
1790885737 48
1790885742 48
1790885747 48
1790885752 48
1790885757 48
1790885762 48
1790885767 48
1790885772 48
1790885777 48
1790885782 48
```
</details>

---

