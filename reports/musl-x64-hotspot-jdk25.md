---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-11-19 13:35:48 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 72-80 cores)</summary>

```
1795112740 80
1795112745 72
1795112750 72
1795112756 72
1795112761 72
1795112766 72
1795112771 74
1795112776 74
1795112781 74
1795112786 74
1795112791 74
1795112796 74
1795112801 72
1795112806 72
1795112811 72
1795112816 72
1795112821 72
1795112826 72
1795112831 72
1795112836 72
```
</details>

---

