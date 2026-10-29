---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 12:43:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1793291846 88
1793291851 88
1793291856 88
1793291861 88
1793291866 88
1793291871 96
1793291876 96
1793291882 96
1793291887 96
1793291892 96
1793291897 96
1793291902 96
1793291907 96
1793291912 88
1793291917 88
1793291922 88
1793291927 88
1793291932 88
1793291937 88
1793291942 88
```
</details>

---

