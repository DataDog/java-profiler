---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 00:09:00 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1794459753 71
1794459758 71
1794459763 71
1794459768 71
1794459773 71
1794459778 71
1794459783 71
1794459788 73
1794459793 73
1794459798 73
1794459803 73
1794459808 73
1794459813 73
1794459818 73
1794459823 73
1794459828 73
1794459834 73
1794459839 73
1794459844 73
1794459849 73
```
</details>

---

