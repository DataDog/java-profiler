---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:42:01 EST

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
| CPU Cores (end) | 65 |
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
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (5 unique values: 65-72 cores)</summary>

```
1794832674 72
1794832679 72
1794832684 72
1794832689 72
1794832694 72
1794832699 67
1794832704 67
1794832709 67
1794832714 67
1794832719 67
1794832724 67
1794832729 67
1794832734 67
1794832739 67
1794832744 67
1794832749 69
1794832754 69
1794832759 69
1794832764 69
1794832769 69
```
</details>

---

