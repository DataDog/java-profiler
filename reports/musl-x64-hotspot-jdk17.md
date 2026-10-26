---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 08:33:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 47-55 cores)</summary>

```
1793017738 55
1793017743 55
1793017748 55
1793017753 55
1793017758 55
1793017763 55
1793017768 55
1793017773 55
1793017778 55
1793017783 55
1793017788 55
1793017793 55
1793017798 55
1793017803 55
1793017808 55
1793017813 55
1793017818 47
1793017823 47
1793017828 47
1793017833 47
```
</details>

---

