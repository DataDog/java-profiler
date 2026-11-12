---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 12:07:08 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 88-93 cores)</summary>

```
1794502922 91
1794502927 91
1794502932 91
1794502937 91
1794502942 93
1794502947 93
1794502952 93
1794502957 93
1794502962 93
1794502967 93
1794502972 93
1794502977 93
1794502982 93
1794502987 93
1794502992 93
1794502997 93
1794503002 93
1794503007 93
1794503012 90
1794503017 90
```
</details>

---

