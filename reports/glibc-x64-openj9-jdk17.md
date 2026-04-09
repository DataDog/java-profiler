---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-09 11:18:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1775747658 41
1775747663 41
1775747668 41
1775747673 41
1775747678 41
1775747683 41
1775747688 41
1775747693 41
1775747698 41
1775747703 41
1775747708 44
1775747713 44
1775747718 48
1775747723 48
1775747728 48
1775747733 48
1775747738 48
1775747743 48
1775747748 48
1775747753 48
```
</details>

---

