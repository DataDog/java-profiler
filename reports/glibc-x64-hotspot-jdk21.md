---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-11 14:07:58 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 50-53 cores)</summary>

```
1773252172 53
1773252177 53
1773252182 53
1773252187 53
1773252192 53
1773252197 53
1773252202 53
1773252207 53
1773252212 53
1773252217 53
1773252222 53
1773252227 53
1773252232 50
1773252237 50
1773252242 50
1773252247 50
1773252252 50
1773252257 50
1773252262 50
1773252267 50
```
</details>

---

