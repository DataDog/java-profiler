---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 06:08:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 39-43 cores)</summary>

```
1794567768 43
1794567773 43
1794567778 43
1794567783 43
1794567788 43
1794567793 41
1794567798 41
1794567803 41
1794567808 41
1794567813 41
1794567818 41
1794567823 41
1794567828 39
1794567833 39
1794567838 39
1794567843 39
1794567848 39
1794567853 39
1794567858 39
1794567863 39
```
</details>

---

