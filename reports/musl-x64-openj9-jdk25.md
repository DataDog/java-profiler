---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:24:31 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 69-79 cores)</summary>

```
1790241514 79
1790241519 79
1790241524 79
1790241529 79
1790241534 79
1790241539 79
1790241544 79
1790241549 69
1790241554 69
1790241559 69
1790241564 69
1790241569 69
1790241574 69
1790241579 69
1790241584 69
1790241589 69
1790241594 69
1790241599 69
1790241604 69
1790241609 69
```
</details>

---

