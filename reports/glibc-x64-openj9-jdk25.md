---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 05:23:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 12 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (6 unique values: 45-74 cores)</summary>

```
1773220554 66
1773220559 66
1773220564 66
1773220569 70
1773220574 70
1773220579 74
1773220584 74
1773220589 48
1773220594 48
1773220599 50
1773220604 50
1773220609 50
1773220614 50
1773220619 50
1773220624 50
1773220629 50
1773220634 50
1773220639 50
1773220644 45
1773220649 45
```
</details>

---

