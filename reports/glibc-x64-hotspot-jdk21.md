---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-14 12:04:47 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 82-96 cores)</summary>

```
1789401544 82
1789401549 82
1789401554 82
1789401559 82
1789401564 82
1789401569 86
1789401574 86
1789401580 88
1789401585 88
1789401590 88
1789401595 88
1789401600 88
1789401605 88
1789401610 88
1789401615 88
1789401620 92
1789401625 92
1789401630 96
1789401635 96
1789401640 96
```
</details>

---

