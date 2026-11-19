---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:35:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 9 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 10 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 21-24 cores)</summary>

```
1795112771 24
1795112776 21
1795112781 21
1795112786 21
1795112791 21
1795112796 21
1795112801 21
1795112806 21
1795112811 21
1795112816 21
1795112821 21
1795112826 21
1795112831 21
1795112836 21
1795112841 21
1795112846 21
1795112851 21
1795112856 21
1795112861 21
1795112866 21
```
</details>

---

