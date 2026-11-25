---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:36:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 10 |
| Allocations | 561 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795620723 85
1795620728 85
1795620733 85
1795620738 85
1795620743 85
1795620748 85
1795620753 85
1795620758 85
1795620763 85
1795620768 85
1795620773 85
1795620778 85
1795620783 87
1795620788 87
1795620793 87
1795620798 87
1795620803 87
1795620808 87
1795620813 87
1795620818 87
```
</details>

---

