---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 16:03:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 34-37 cores)</summary>

```
1790193536 37
1790193541 37
1790193546 37
1790193551 37
1790193556 37
1790193561 37
1790193566 37
1790193571 37
1790193576 37
1790193581 37
1790193586 37
1790193591 37
1790193596 37
1790193601 37
1790193606 37
1790193611 37
1790193616 35
1790193621 35
1790193626 35
1790193631 35
```
</details>

---

