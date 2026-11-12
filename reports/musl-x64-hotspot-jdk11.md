---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:40:45 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 77-88 cores)</summary>

```
1794504864 88
1794504869 88
1794504874 88
1794504879 88
1794504885 88
1794504890 88
1794504895 88
1794504900 88
1794504905 88
1794504910 88
1794504915 86
1794504920 86
1794504925 86
1794504930 86
1794504935 77
1794504940 77
1794504945 77
1794504950 77
1794504955 77
1794504960 77
```
</details>

---

