---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:58:27 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 11 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (4 unique values: 61-68 cores)</summary>

```
1770828747 65
1770828752 65
1770828757 65
1770828762 65
1770828767 65
1770828772 65
1770828777 65
1770828782 65
1770828787 65
1770828792 65
1770828797 65
1770828802 65
1770828807 61
1770828812 61
1770828817 61
1770828822 68
1770828827 68
1770828832 63
1770828837 63
1770828842 63
```
</details>

---

