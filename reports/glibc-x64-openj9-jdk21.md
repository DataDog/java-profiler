---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 18:25:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1792707689 24
1792707694 32
1792707699 32
1792707704 32
1792707709 32
1792707714 32
1792707719 32
1792707724 32
1792707729 32
1792707734 32
1792707739 32
1792707744 32
1792707749 32
1792707754 32
1792707759 32
1792707764 32
1792707769 32
1792707774 32
1792707779 32
1792707784 30
```
</details>

---

