---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-09 12:24:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794244737 48
1794244742 48
1794244747 48
1794244752 48
1794244757 48
1794244762 43
1794244767 43
1794244772 43
1794244777 43
1794244782 43
1794244787 43
1794244792 43
1794244797 43
1794244802 43
1794244807 43
1794244812 43
1794244817 43
1794244822 43
1794244827 43
1794244832 46
```
</details>

---

