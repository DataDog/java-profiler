---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 09:50:44 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 8 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1790084788 11
1790084793 11
1790084798 11
1790084803 11
1790084808 11
1790084813 11
1790084818 11
1790084823 11
1790084828 11
1790084833 11
1790084838 11
1790084843 11
1790084848 11
1790084853 32
1790084858 32
1790084863 32
1790084868 32
1790084873 32
1790084878 32
1790084883 32
```
</details>

---

