---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-13 12:15:36 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 44-68 cores)</summary>

```
1773418133 44
1773418138 44
1773418143 44
1773418148 44
1773418153 44
1773418158 44
1773418163 44
1773418168 44
1773418173 44
1773418178 44
1773418183 44
1773418188 44
1773418193 44
1773418198 44
1773418203 44
1773418208 44
1773418213 63
1773418218 63
1773418223 65
1773418228 65
```
</details>

---

