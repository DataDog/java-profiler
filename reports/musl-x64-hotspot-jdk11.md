---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-08 08:36:47 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 72-96 cores)</summary>

```
1791462730 72
1791462735 72
1791462740 72
1791462745 72
1791462750 72
1791462755 72
1791462760 72
1791462765 72
1791462770 72
1791462775 72
1791462780 72
1791462785 96
1791462790 96
1791462795 96
1791462800 96
1791462805 96
1791462810 96
1791462815 96
1791462820 96
1791462825 96
```
</details>

---

