---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:41:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 56-76 cores)</summary>

```
1795199740 58
1795199745 56
1795199750 56
1795199755 56
1795199760 56
1795199765 56
1795199770 56
1795199775 56
1795199780 56
1795199785 56
1795199790 56
1795199795 76
1795199800 76
1795199805 76
1795199810 76
1795199815 76
1795199820 76
1795199825 76
1795199830 74
1795199835 74
```
</details>

---

