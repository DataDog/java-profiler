---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 05:55:46 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1792403440 96
1792403445 96
1792403450 88
1792403455 88
1792403460 88
1792403465 88
1792403470 88
1792403475 88
1792403480 88
1792403485 88
1792403490 88
1792403495 88
1792403500 88
1792403505 88
1792403510 88
1792403515 88
1792403520 88
1792403525 88
1792403530 88
1792403535 88
```
</details>

---

