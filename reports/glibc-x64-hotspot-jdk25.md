---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:28:10 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791530618 30
1791530623 30
1791530628 30
1791530633 30
1791530638 30
1791530643 30
1791530648 30
1791530653 30
1791530658 30
1791530663 30
1791530668 32
1791530673 32
1791530678 32
1791530683 32
1791530688 32
1791530693 32
1791530698 32
1791530703 32
1791530708 32
1791530713 32
```
</details>

---

