---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:29:29 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (5 unique values: 68-76 cores)</summary>

```
1789680177 76
1789680182 76
1789680187 76
1789680192 76
1789680197 74
1789680202 74
1789680207 74
1789680212 74
1789680217 72
1789680222 72
1789680227 72
1789680232 72
1789680237 72
1789680242 72
1789680247 72
1789680252 72
1789680257 68
1789680262 68
1789680267 68
1789680272 68
```
</details>

---

