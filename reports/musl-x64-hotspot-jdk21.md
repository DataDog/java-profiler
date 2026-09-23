---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-23 07:03:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1790161207 70
1790161212 70
1790161217 70
1790161222 70
1790161227 70
1790161232 70
1790161237 70
1790161242 70
1790161248 70
1790161253 70
1790161258 70
1790161263 70
1790161268 70
1790161273 70
1790161278 72
1790161283 72
1790161288 72
1790161293 72
1790161298 72
1790161303 72
```
</details>

---

