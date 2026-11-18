---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1795010733 85
1795010738 85
1795010743 85
1795010748 85
1795010753 85
1795010758 87
1795010763 87
1795010768 87
1795010773 87
1795010778 87
1795010783 87
1795010788 85
1795010793 85
1795010798 85
1795010803 85
1795010808 85
1795010813 85
1795010818 85
1795010823 85
1795010828 85
```
</details>

---

