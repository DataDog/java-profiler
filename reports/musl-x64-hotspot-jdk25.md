---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 13:39:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 11 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 12 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 52-56 cores)</summary>

```
1773250174 52
1773250179 52
1773250184 52
1773250189 52
1773250194 52
1773250199 52
1773250204 52
1773250209 52
1773250214 52
1773250219 54
1773250224 54
1773250229 54
1773250234 54
1773250239 56
1773250244 56
1773250249 56
1773250254 56
1773250259 56
1773250264 56
1773250269 56
```
</details>

---

