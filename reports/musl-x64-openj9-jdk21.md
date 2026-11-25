---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:36:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 68-72 cores)</summary>

```
1795620709 72
1795620714 72
1795620719 72
1795620724 72
1795620729 72
1795620734 70
1795620739 70
1795620744 70
1795620749 70
1795620754 70
1795620759 70
1795620764 70
1795620769 70
1795620774 70
1795620779 70
1795620784 70
1795620789 70
1795620794 70
1795620799 70
1795620804 70
```
</details>

---

