---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:33:12 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 349 |
| Sample Rate | 5.82/sec |
| Health Score | 364% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 22-28 cores)</summary>

```
1789680178 28
1789680183 28
1789680188 28
1789680193 28
1789680198 28
1789680204 28
1789680209 28
1789680214 28
1789680219 28
1789680224 28
1789680229 28
1789680234 28
1789680239 28
1789680244 28
1789680249 28
1789680254 22
1789680259 22
1789680264 22
1789680269 22
1789680274 22
```
</details>

---

