---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 27.00/sec |
| Health Score | 1688% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1769702692 36
1769702697 36
1769702702 36
1769702707 31
1769702712 31
1769702717 36
1769702722 36
1769702727 36
1769702732 36
1769702737 36
1769702742 36
1769702747 36
1769702752 36
1769702757 36
1769702762 36
1769702767 36
1769702772 36
1769702777 36
1769702782 36
1769702787 36
```
</details>

---

