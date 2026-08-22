---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-22 13:05:53 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787418095 64
1787418100 64
1787418105 64
1787418110 66
1787418115 66
1787418120 66
1787418125 66
1787418130 66
1787418135 66
1787418140 66
1787418145 66
1787418150 66
1787418155 66
1787418160 66
1787418165 66
1787418170 66
1787418175 66
1787418180 66
1787418185 66
1787418190 66
```
</details>

---

