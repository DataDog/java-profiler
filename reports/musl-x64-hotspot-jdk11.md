---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:33:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 85-88 cores)</summary>

```
1789680164 85
1789680169 85
1789680174 85
1789680179 85
1789680184 85
1789680189 85
1789680194 85
1789680199 85
1789680204 85
1789680209 87
1789680214 87
1789680219 87
1789680224 88
1789680229 88
1789680234 88
1789680239 88
1789680244 88
1789680249 88
1789680254 88
1789680259 88
```
</details>

---

