---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:08:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 164 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 13 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794999758 39
1794999763 39
1794999768 39
1794999773 39
1794999778 39
1794999783 39
1794999788 39
1794999793 39
1794999798 39
1794999803 39
1794999808 39
1794999813 39
1794999818 39
1794999823 39
1794999828 39
1794999833 34
1794999838 34
1794999843 34
1794999848 34
1794999853 34
```
</details>

---

