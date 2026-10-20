---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 12:18:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 10 |
| Allocations | 410 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792512733 32
1792512738 32
1792512743 32
1792512748 32
1792512753 30
1792512758 30
1792512763 30
1792512768 30
1792512773 30
1792512778 30
1792512783 30
1792512788 30
1792512793 30
1792512798 30
1792512803 30
1792512808 30
1792512813 30
1792512818 30
1792512823 30
1792512828 30
```
</details>

---

