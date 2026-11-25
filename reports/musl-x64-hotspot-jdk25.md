---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:18:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 77-87 cores)</summary>

```
1795626763 77
1795626768 77
1795626773 77
1795626778 77
1795626783 77
1795626788 77
1795626793 77
1795626798 77
1795626803 77
1795626808 77
1795626813 85
1795626819 85
1795626824 85
1795626829 85
1795626834 85
1795626839 85
1795626844 85
1795626849 85
1795626854 85
1795626859 85
```
</details>

---

