---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 08:36:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 39-52 cores)</summary>

```
1791462743 39
1791462748 52
1791462753 52
1791462758 52
1791462763 52
1791462768 52
1791462773 52
1791462778 41
1791462783 41
1791462788 41
1791462793 41
1791462798 41
1791462803 41
1791462808 41
1791462813 41
1791462818 41
1791462823 41
1791462828 41
1791462833 41
1791462838 41
```
</details>

---

