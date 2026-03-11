---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 13:17:29 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 10 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 13 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (6 unique values: 59-76 cores)</summary>

```
1773249107 59
1773249112 59
1773249117 59
1773249122 59
1773249127 59
1773249132 59
1773249137 68
1773249142 68
1773249147 72
1773249152 72
1773249157 72
1773249162 72
1773249167 72
1773249172 72
1773249177 74
1773249182 74
1773249187 74
1773249192 76
1773249197 76
1773249202 76
```
</details>

---

