---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:28:14 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1795641761 60
1795641766 58
1795641771 58
1795641776 58
1795641781 58
1795641786 58
1795641792 58
1795641797 58
1795641802 58
1795641807 58
1795641812 58
1795641817 58
1795641822 58
1795641827 58
1795641832 58
1795641837 58
1795641842 58
1795641847 58
1795641852 58
1795641857 58
```
</details>

---

