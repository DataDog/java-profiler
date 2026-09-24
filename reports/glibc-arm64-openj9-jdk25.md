---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:24:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 36 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (4 unique values: 40-46 cores)</summary>

```
1790241556 40
1790241561 40
1790241566 45
1790241571 45
1790241576 45
1790241581 45
1790241586 45
1790241591 45
1790241596 45
1790241601 45
1790241606 46
1790241611 46
1790241616 43
1790241621 43
1790241626 43
1790241631 43
1790241636 43
1790241641 43
1790241646 43
1790241651 43
```
</details>

---

