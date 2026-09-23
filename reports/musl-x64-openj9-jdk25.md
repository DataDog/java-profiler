---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 16:03:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 66-72 cores)</summary>

```
1790193521 66
1790193526 66
1790193531 70
1790193536 70
1790193541 70
1790193546 70
1790193551 70
1790193556 70
1790193561 70
1790193566 70
1790193571 70
1790193576 70
1790193581 70
1790193586 70
1790193591 70
1790193596 72
1790193601 72
1790193606 72
1790193611 72
1790193616 72
```
</details>

---

