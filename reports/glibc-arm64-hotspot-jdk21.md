---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:35:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 11 |
| Allocations | 109 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (3 unique values: 31-50 cores)</summary>

```
1795112766 31
1795112771 31
1795112776 31
1795112781 31
1795112786 31
1795112791 31
1795112796 31
1795112801 31
1795112806 36
1795112811 36
1795112816 36
1795112821 36
1795112826 36
1795112831 36
1795112836 50
1795112841 50
1795112846 36
1795112851 36
1795112856 36
1795112861 36
```
</details>

---

