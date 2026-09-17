---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:29:30 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 64-75 cores)</summary>

```
1789680087 66
1789680092 66
1789680097 64
1789680102 64
1789680107 64
1789680112 64
1789680117 64
1789680122 66
1789680127 66
1789680132 66
1789680137 66
1789680142 66
1789680147 66
1789680152 66
1789680157 66
1789680162 66
1789680167 66
1789680172 66
1789680177 66
1789680182 66
```
</details>

---

