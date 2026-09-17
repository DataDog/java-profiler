---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 41-49 cores)</summary>

```
1789686623 41
1789686628 41
1789686633 49
1789686638 49
1789686643 49
1789686648 49
1789686653 49
1789686658 49
1789686663 49
1789686668 49
1789686673 49
1789686678 49
1789686683 49
1789686688 49
1789686693 49
1789686698 49
1789686703 49
1789686708 49
1789686713 49
1789686718 49
```
</details>

---

