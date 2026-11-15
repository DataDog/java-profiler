---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 00:06:16 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 8 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 59-81 cores)</summary>

```
1794718831 59
1794718836 59
1794718841 59
1794718846 59
1794718851 59
1794718856 59
1794718861 59
1794718866 59
1794718871 59
1794718876 59
1794718881 59
1794718886 59
1794718891 59
1794718896 59
1794718901 59
1794718906 61
1794718911 61
1794718916 61
1794718921 81
1794718926 81
```
</details>

---

