---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 16:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (5 unique values: 43-65 cores)</summary>

```
1777321177 46
1777321182 46
1777321187 46
1777321192 46
1777321197 46
1777321202 46
1777321207 46
1777321212 46
1777321217 46
1777321222 46
1777321227 65
1777321232 65
1777321237 46
1777321242 46
1777321247 46
1777321252 46
1777321257 46
1777321262 46
1777321267 46
1777321272 45
```
</details>

---

