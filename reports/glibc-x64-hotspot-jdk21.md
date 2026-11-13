---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 16:23:57 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (6 unique values: 52-75 cores)</summary>

```
1794604747 56
1794604752 56
1794604757 56
1794604762 56
1794604767 56
1794604772 54
1794604777 54
1794604782 52
1794604787 52
1794604792 52
1794604797 52
1794604802 52
1794604807 52
1794604812 52
1794604817 56
1794604822 56
1794604827 56
1794604832 56
1794604837 75
1794604842 75
```
</details>

---

