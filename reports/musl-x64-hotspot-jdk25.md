---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 74-78 cores)</summary>

```
1794999743 78
1794999748 76
1794999753 76
1794999758 76
1794999763 76
1794999768 76
1794999773 76
1794999778 76
1794999783 76
1794999788 76
1794999793 76
1794999798 76
1794999803 76
1794999808 74
1794999813 74
1794999818 74
1794999823 74
1794999828 74
1794999833 74
1794999838 74
```
</details>

---

