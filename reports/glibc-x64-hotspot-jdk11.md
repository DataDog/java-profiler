---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 10:07:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 63-67 cores)</summary>

```
1770130836 65
1770130841 65
1770130846 63
1770130851 63
1770130856 63
1770130861 63
1770130866 63
1770130871 63
1770130876 63
1770130881 63
1770130886 63
1770130891 63
1770130896 65
1770130901 65
1770130906 67
1770130911 67
1770130916 67
1770130921 67
1770130926 67
1770130931 67
```
</details>

---

