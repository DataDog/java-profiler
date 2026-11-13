---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:08:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 8 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1794567733 12
1794567738 12
1794567743 12
1794567748 12
1794567753 12
1794567758 12
1794567763 12
1794567768 12
1794567773 12
1794567778 12
1794567783 12
1794567788 12
1794567793 12
1794567798 12
1794567803 12
1794567808 10
1794567813 10
1794567818 10
1794567823 10
1794567828 10
```
</details>

---

