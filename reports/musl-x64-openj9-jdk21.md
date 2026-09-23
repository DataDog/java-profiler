---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 16:03:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 58-64 cores)</summary>

```
1790193521 58
1790193526 58
1790193531 58
1790193536 58
1790193541 58
1790193546 58
1790193551 58
1790193556 64
1790193561 64
1790193566 64
1790193571 64
1790193576 64
1790193581 64
1790193586 64
1790193591 64
1790193596 64
1790193601 64
1790193606 64
1790193611 64
1790193616 62
```
</details>

---

