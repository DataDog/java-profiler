---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795529736 59
1795529741 59
1795529746 59
1795529751 59
1795529756 64
1795529761 64
1795529766 64
1795529771 64
1795529776 64
1795529781 64
1795529786 64
1795529791 64
1795529796 64
1795529801 64
1795529806 64
1795529811 64
1795529816 64
1795529821 64
1795529826 64
1795529831 64
```
</details>

---

