---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 05:47:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 14-47 cores)</summary>

```
1795344198 33
1795344203 16
1795344208 16
1795344213 16
1795344218 16
1795344223 16
1795344228 16
1795344233 16
1795344238 16
1795344243 16
1795344248 14
1795344253 14
1795344258 14
1795344263 14
1795344268 14
1795344273 14
1795344278 14
1795344283 14
1795344288 47
1795344293 47
```
</details>

---

