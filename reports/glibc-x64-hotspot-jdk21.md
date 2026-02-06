---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-05 20:41:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 10 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 13 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 38-46 cores)</summary>

```
1770341743 38
1770341748 38
1770341753 38
1770341759 38
1770341764 38
1770341769 38
1770341774 38
1770341779 38
1770341784 38
1770341789 38
1770341794 46
1770341799 46
1770341804 42
1770341809 42
1770341814 42
1770341819 42
1770341824 42
1770341829 42
1770341834 44
1770341839 44
```
</details>

---

