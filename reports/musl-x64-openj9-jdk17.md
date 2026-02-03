---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 05:39:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 10 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 49-70 cores)</summary>

```
1770114752 70
1770114757 68
1770114762 68
1770114767 68
1770114772 68
1770114777 53
1770114782 53
1770114787 53
1770114792 49
1770114797 49
1770114802 55
1770114807 55
1770114812 55
1770114817 55
1770114822 55
1770114827 55
1770114832 55
1770114837 55
1770114842 55
1770114847 55
```
</details>

---

