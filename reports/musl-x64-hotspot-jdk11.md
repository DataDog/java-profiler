---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:50:03 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 956 |
| Sample Rate | 15.93/sec |
| Health Score | 996% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 75-76 cores)</summary>

```
1778514212 76
1778514217 76
1778514222 76
1778514227 76
1778514232 76
1778514237 75
1778514242 75
1778514247 75
1778514252 76
1778514257 76
1778514262 76
1778514267 76
1778514272 76
1778514277 76
1778514282 76
1778514287 76
1778514292 76
1778514297 76
1778514302 76
1778514307 76
```
</details>

---

