---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 16:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 39-55 cores)</summary>

```
1790281593 45
1790281598 55
1790281603 55
1790281608 39
1790281613 39
1790281618 39
1790281623 39
1790281628 39
1790281633 39
1790281638 39
1790281643 39
1790281648 39
1790281653 39
1790281658 39
1790281664 39
1790281669 39
1790281674 39
1790281679 39
1790281684 39
1790281689 39
```
</details>

---

