---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 34-35 cores)</summary>

```
1794999733 35
1794999738 35
1794999743 35
1794999748 35
1794999753 35
1794999758 34
1794999763 34
1794999768 34
1794999773 34
1794999778 35
1794999783 35
1794999788 35
1794999793 35
1794999798 35
1794999803 35
1794999808 35
1794999813 35
1794999818 35
1794999823 35
1794999828 35
```
</details>

---

